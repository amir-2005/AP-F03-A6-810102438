#include "Utaste.hpp"

UTaste::UTaste(string path_to_restaurants, string path_to_districts)
{
    loadRestaurantData(path_to_restaurants);
    loadDistrictsData(path_to_districts);
}

void UTaste::loadRestaurantData(string path_to_restaurants)
{
    ifstream rests_file(path_to_restaurants);
    string line;
    if (!rests_file)
        throw(invalid_argument("Cant open " + path_to_restaurants));

    getline(rests_file, line);

    while (getline(rests_file, line))
    {
        stringstream ss(line);
        string name, district, foods_prices, open_time_str, close_time_str, number_of_tables_str;

        getline(ss, name, DELIM);
        getline(ss, district, DELIM);
        getline(ss, foods_prices, DELIM);
        getline(ss, open_time_str, DELIM);
        getline(ss, close_time_str, DELIM);
        getline(ss, number_of_tables_str, DELIM);

        int open_time = stoi(open_time_str);
        int close_time = stoi(close_time_str);
        int number_of_tables = stoi(number_of_tables_str);

        map<food, int> menu;
        stringstream food_ss(foods_prices);
        string food_price_pair;

        while (getline(food_ss, food_price_pair, INNER_DELIM))
        {
            int colon_pos = food_price_pair.find(PRICE_DELIM);
            if (colon_pos != string::npos)
            {
                string food_name = food_price_pair.substr(0, colon_pos);
                int price = stoi(food_price_pair.substr(colon_pos + 1));
                menu[food_name] = price;
            }
            else
                throw(invalid_argument("Input file format is incorrect"));
        }

        shared_ptr<Restaurant> restaurant = make_shared<Restaurant>(name, district, number_of_tables, menu, open_time, close_time);
        rests.push_back(restaurant);
    }

    rests_file.close();
}

void UTaste::loadDistrictsData(string path_to_districts)
{

    ifstream districts_file(path_to_districts);
    if (!districts_file)
        throw(invalid_argument("Cant open " + path_to_districts));

    vector<vector<string>> neighbors;
    string line, district_name, neighbor_name;
    int i = 0;

    getline(districts_file, line);
    while (getline(districts_file, line))
    {
        neighbors.push_back({});
        stringstream ss(line);
        getline(ss, district_name, DELIM);

        districts.push_back(make_shared<District>(district_name));

        while (getline(ss, neighbor_name, INNER_DELIM))
            neighbors[i].push_back(neighbor_name);

        i++;
    }

    for (int i = 0; i < districts.size(); i++)
        for (auto name : neighbors[i])
            for (auto d : districts)
                if (name == d->name)
                    districts[i]->neighbors.push_back(d);

    districts_file.close();

    sort(districts.begin(), districts.end(), [](shared_ptr<District> &a, shared_ptr<District> &b)
         { return a->name < b->name; });

    for (auto r : rests)
        for (auto d : districts)
            if (r->district_name == d->name)
            {
                d->rests.push_back(r);
                break;
            }
}

void UTaste::signUp(string username, string password)
{
    if (logged_in == true)
        throw(PermissionDenied("can't sign up while logged in"));

    for (auto u : users)
        if (u->getName() == username)
            throw(BadRequest("The user is already signed up"));

    users.push_back(make_shared<User>(username, password));
}

void UTaste::login(string username, string password)
{
    if (logged_in == true)
        throw(PermissionDenied("can't login twice"));

    for (auto u : users)
    {
        if (u->getName() == username)
        {
            if (u->getPassword() == password)
            {
                logged_in = true;
                current_user = u;
                return;
            }
            else
                throw(PermissionDenied("wrong password"));
        }
    }
    throw(NotFound(username + MSG_NOT_FOUND));
}

void UTaste::logout()
{
    if (logged_in == false)
        throw(PermissionDenied("can't logout before login"));

    logged_in = false;
    current_user = nullptr;
}

void UTaste::setUserDistrict(string district_name)
{
    if (logged_in == false)
        throw(PermissionDenied("no user has logged in"));

    for (auto d : districts)
        if (d->name == district_name)
        {
            current_user->setDistrict(d);
            return;
        }

    throw(NotFound(district_name + MSG_NOT_FOUND));
}

string UTaste::setReservation(string restaurant_name, int table_id, time_period reserve_time, map<food, int> foods)
{
    if (logged_in == false)
        throw(PermissionDenied("no user has logged in"));

    if (!current_user->canReserveInThisTime(reserve_time))
        throw(PermissionDenied("reservation time is invalid"));

    shared_ptr<Reservation> reservation = make_shared<Reservation>(restaurant_name, table_id, reserve_time, foods);
    for (auto rest : rests)
        if (rest->name == restaurant_name)
        {
            rest->reserveTable(reservation, table_id);
            current_user->addReservation(reservation);
            return reservation->getInfo();
        }
    throw(NotFound(restaurant_name + MSG_NOT_FOUND));
}

string UTaste::getDistrictsInfo(string district_name)
{
    if (logged_in == false)
        throw(PermissionDenied("no user has logged in"));

    string output = "";

    if (districts.empty())
        throw(Empty("there is no district"));

    if (!district_name.empty())
    {
        for (auto d : districts)
            if (d->name == district_name)
            {
                output += d->name + ": ";
                for (auto n : d->neighbors)
                    output += n->name + ", ";

                output.erase(output.size() - 2);
                output += "\n";
                return output;
            }
        throw(NotFound(district_name + MSG_NOT_FOUND));
    }

    for (auto d : districts)
    {
        output += d->name + ": ";
        for (auto n : d->neighbors)
            output += n->name + ", ";

        output.erase(output.size() - 2);
        output += "\n";
    }

    return output;
}

string UTaste::getRestaurantsList(food food)
{
    if (logged_in == false)
        throw(PermissionDenied("no user has logged in"));

    if (current_user->distric == nullptr)
        throw(NotFound("user district in not set"));

    vector<string> visited;
    string output = "";

    restaurantBFS(current_user->distric, visited, output, food);

    if (output.empty())
        throw(Empty("no restaurant with this food :" + food));

    return output;
}

string UTaste::getRestaurantInfo(string restaurant_name)
{
    if (logged_in == false)
        throw(PermissionDenied("no user has logged in"));

    shared_ptr<Restaurant> restaurant;

    for (auto r: rests)
        if (r->name == restaurant_name)
        {
            restaurant = r;
            break;
        }

    if (restaurant == nullptr)
        throw(NotFound(restaurant_name + MSG_NOT_FOUND));

    return restaurant->getInfo();
}

void UTaste::restaurantBFS(shared_ptr<District> district, vector<string> &visited, string &output, food &food)
{
    if (find(visited.begin(), visited.end(), district->name) == visited.end())
    {
        for (auto r : district->rests)
        {
            if (food.empty() || (r->isInMenu(food)))
                output += r->name + "(" + district->name + ")\n";
        }
        visited.push_back(district->name);
        for (auto n: district->neighbors)
            restaurantBFS(n, visited, output, food);
    }
}

string UTaste::showReservations(string restaurant_name, int reserve_id)
{
    for (auto user:users)
        if (user != current_user && user->hasThisReservation(restaurant_name, reserve_id))
            throw(PermissionDenied("the reservation is belong to someone else"));

    return current_user->getReservationsInfo(restaurant_name, reserve_id);
}

void UTaste::deleteReservation(string restaurant_name, int reserve_id)
{
    for (auto user:users)
        if (user != current_user && user->hasThisReservation(restaurant_name, reserve_id))
            throw(PermissionDenied("the reservation is belong to someone else"));

    current_user->removeReservation(restaurant_name, reserve_id);
    
}

// void UTaste::test()
// {
//     if (current_user == nullptr)
//         return;
//     for (auto r : current_user->reservs)
//         cout << r->restaurant_name << ":" << r->id << endl;
// }
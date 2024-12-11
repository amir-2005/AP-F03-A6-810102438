#include "Utaste.hpp"

UTaste::UTaste(string path_to_restaurants, string path_to_districts)
{
    loadDistrictsData(path_to_districts);
    loadRestaurantData(path_to_restaurants);
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

        shared_ptr<Restaurant> restaurant = make_shared<Restaurant>(name, number_of_tables, menu, open_time, close_time);
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
        {
            neighbors[i].push_back(neighbor_name);
        }

        i++;
    }

    // TODO : SORT DISTRICT VECTOR
    districts_file.close();
}

void UTaste::addUser(string username, string password)
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
    throw(NotFound("user does not exist"));
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
    for (auto d:districts)
        if (d->name == district_name)
        {
            current_user->setDistrict(d);
            return;
        }

    throw(NotFound("district not found"));
}

void UTaste::setReservation(string restaurant_name, int table_id, time_period reserve_time, vector<food> foods)
{
    // TODO : create reservaion id for each reserve at restaurant class , 
    // shared_ptr<Reservation> resrvation = make_sahred(restaurant_name, )
}

// void UTaste::test()
// {
//     for (auto u:users)
//         cout << "test" << u->getName() << endl;
// }
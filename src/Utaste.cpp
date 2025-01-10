#include "Utaste.hpp"

UTaste::UTaste(string path_to_restaurants, string path_to_districts, string path_to_discounts)
{
    loadRestaurantData(path_to_restaurants);
    loadDistrictsData(path_to_districts);
    loadDiscountsData(path_to_discounts);
}

void UTaste::loadRestaurantData(string path_to_restaurants)
{
    ifstream rests_file(path_to_restaurants);
    string line;
    if (!rests_file)
        throw(invalid_argument(UNEXPECTED_ERROR_FILE_OPEN + path_to_restaurants));

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
                throw(invalid_argument(UNEXPECTED_ERROR_FILE_FORMAT));
        }

        shared_ptr<Restaurant> restaurant = make_shared<Restaurant>(name, district, number_of_tables, menu, open_time, close_time);
        rests.push_back(restaurant);
    }

    sort(rests.begin(), rests.end(), [](shared_ptr<Restaurant> &a, shared_ptr<Restaurant> &b)
         { return a->name < b->name; });

    rests_file.close();
}

void UTaste::loadDistrictsData(string path_to_districts)
{

    ifstream districts_file(path_to_districts);
    if (!districts_file)
        throw(invalid_argument(UNEXPECTED_ERROR_FILE_OPEN + path_to_districts));

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

void UTaste::loadDiscountsData(string path_to_discounts)
{
    ifstream disc_file(path_to_discounts);
    string line;
    if (!disc_file)
        throw(invalid_argument(UNEXPECTED_ERROR_FILE_OPEN + path_to_discounts));

    getline(disc_file, line);
    while (getline(disc_file, line))
    {
        stringstream ss(line);
        string rest_name, total_price, first_order, food_discounts;
        shared_ptr<Restaurant> restaurant;

        getline(ss, rest_name, DELIM);
        getline(ss, total_price, DELIM);
        getline(ss, first_order, DELIM);
        getline(ss, food_discounts, DELIM);

        for (auto r : rests)
            if (r->name == rest_name)
                restaurant = r;

        if (food_discounts != NO_DISCOUNT)
        {
            stringstream foods_ss(food_discounts);
            string food_discount;
            while (getline(foods_ss, food_discount, DISCOUNT_DELIM))
            {
                string type, value, food_name;
                stringstream food_discount_ss(food_discount);
                getline(food_discount_ss, type, INNER_DELIM);
                getline(food_discount_ss, food_name, PRICE_DELIM);
                getline(food_discount_ss, value);
                int food_price = restaurant->getPriceInMenu(food_name);
                restaurant->discounts.push_back(make_shared<FoodDiscount>(type, stoi(value), food_name, food_price));
            }
        }

        if (first_order != NO_DISCOUNT)
        {
            string type, value;
            stringstream first_order_ss(first_order);
            getline(first_order_ss, type, INNER_DELIM);
            getline(first_order_ss, value, INNER_DELIM);

            restaurant->discounts.push_back(make_shared<FirstOrderDiscount>(type, stoi(value)));
        }

        if (total_price != NO_DISCOUNT)
        {
            string type, min, value;
            stringstream total_price_ss(total_price);
            getline(total_price_ss, type, INNER_DELIM);
            getline(total_price_ss, min, INNER_DELIM);
            getline(total_price_ss, value, INNER_DELIM);

            restaurant->discounts.push_back(make_shared<TotalPriceDiscount>(type, stoi(value), stoi(min)));
        }
    }
}

void UTaste::signUp(string username, string password)
{
    if (logged_in == true)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_SIGN_UP));

    for (auto u : users)
        if (u->getName() == username)
            throw(BadRequest(MSG_PERMISSION_DENIED_DUPLICATED));

    users.push_back(make_shared<User>(username, password));
    current_user = users.back();
    logged_in = true;
}

void UTaste::login(string username, string password)
{
    if (logged_in == true)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_LOGIN));

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
                throw(PermissionDenied(MSG_PERMISSION_DENIED_PASSWORD));
        }
    }
    throw(NotFound(username + MSG_NOT_FOUND));
}

void UTaste::logout()
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    logged_in = false;
    current_user = nullptr;
}

void UTaste::setUserDistrict(string district_name)
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

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
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    if (!current_user->canReserveInThisTime(reserve_time))
        throw(PermissionDenied(MSG_PERMISSION_DENIED_RESERVE_TIME));

    shared_ptr<Reservation> reservation = make_shared<Reservation>(restaurant_name, table_id, reserve_time, foods);
    for (auto rest : rests)
        if (rest->name == restaurant_name)
        {
            int final_bill = rest->reserveTable(reservation, table_id);
            if (final_bill > current_user->budget)
            {
                rest->removeReservation(reservation->id);
                rest->reduce_id();
                throw(BadRequest(MSG_BAD_REQUEST_LOW_BUDGET));
            }
            current_user->budget -= final_bill;
            current_user->addReservation(reservation);
            return reservation->getInfo();
        }
    throw(NotFound(restaurant_name + MSG_NOT_FOUND));
}

string UTaste::getDistrictsInfo(string district_name)
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    string output = "";

    if (districts.empty())
        throw(Empty(MSG_EMPTY_NO_DISTRICT));

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
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    if (current_user->distric == nullptr)
        throw(NotFound(MSG_NOT_FOUND_DISTRICT_SET));

    vector<string> visited;
    string output = "";

    list<shared_ptr<District>> queue = {current_user->distric};
    restaurantBFS(current_user->distric, visited, queue , output, food);

    if (output.empty())
        throw(Empty(MSG_EMPTY_NO_RESTAURANT + food));

    return output;
}

string UTaste::getRestaurantInfo(string restaurant_name)
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    shared_ptr<Restaurant> restaurant;

    for (auto r : rests)
        if (r->name == restaurant_name)
        {
            restaurant = r;
            break;
        }

    if (restaurant == nullptr)
        throw(NotFound(restaurant_name + MSG_NOT_FOUND));

    return restaurant->getInfo();
}

void UTaste::restaurantBFS(shared_ptr<District> district, vector<string> &visited, list<shared_ptr<District>> queue, string &output, food &food)
{
    if (find(visited.begin(), visited.end(), district->name) == visited.end())
    {
        for (auto r : district->rests)
        {
            if (food.empty() || (r->getPriceInMenu(food) != 0))
                output += r->name + " (" + district->name + ")\n";
        }
        visited.push_back(district->name);
        queue.pop_front();
        for (auto n : district->neighbors)
            if (find(queue.begin(), queue.end(), n) == queue.end())
                queue.push_back(n);

        for (auto d : queue)
            restaurantBFS(d, visited, queue, output,food);
    }
}

string UTaste::showReservations(string restaurant_name, int reserve_id)
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    for (auto user : users)
        if (user != current_user && user->hasThisReservation(restaurant_name, reserve_id))
            throw(PermissionDenied(MSG_PERMISSION_DENIED_RESERVATION));

    return current_user->getReservationsInfo(restaurant_name, reserve_id);
}

void UTaste::deleteReservation(string restaurant_name, int reserve_id)
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    for (auto user : users)
        if (user != current_user && user->hasThisReservation(restaurant_name, reserve_id))
            throw(PermissionDenied(MSG_PERMISSION_DENIED_RESERVATION));

    current_user->removeReservation(restaurant_name, reserve_id);
    
    for (auto r : rests)
        if (r->name == restaurant_name)
            r->removeReservation(reserve_id);
}

string UTaste::showBudget()
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));

    return to_string(current_user->budget);
}

void UTaste::increaseBudget(int amount)
{
    if (logged_in == false)
        throw(PermissionDenied(MSG_PERMISSION_DENIED_NO_USER));
    if (amount < 0)
        throw(BadRequest(MSG_BAD_REQUEST_NEGATIVE));
    current_user->budget += amount;
}
#include "Reservation.hpp"

Reservation::Reservation(int _id, string _restaurant_name, time_period _time, map<food, int> _foods, shared_ptr<User> _user)
{
    id = _id;
    restaurant_name = _restaurant_name;
    time = _time;
    foods = _foods;
    user = _user;
}

string Reservation::getInfo()
{
    string output = "";
    output += to_string(id) + ": " + restaurant_name + " " + to_string(table_id) + " ";
    output += to_string(time.first) + "-" + to_string(time.second);
    for (auto f: foods)
        output += " " + f.first + "(" + to_string(f.second) + ")";
    output = "\n";
    return output;
}

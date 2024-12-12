#include "Reservation.hpp"

Reservation::Reservation(string _restaurant_name, time_period _time, map<food, int> _foods, shared_ptr<User> _user)
{
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

bool Reservation :: checkTimeInterference(time_period time_limit, bool shoud_be_in)
{
    if (shoud_be_in)
        return (time.second > time_limit.second) || (time.first < time_limit.first);
    else 
        return (time.second > time_limit.first) || (time.first < time_limit.second);
}

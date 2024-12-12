#include "Reservation.hpp"

Reservation::Reservation(string _restaurant_name, int _table_id, time_period _time, map<food, int> _foods)
{
    restaurant_name = _restaurant_name;
    table_id = _table_id;
    time = _time;
    foods = _foods;
}

string Reservation::getTotalInfo()
{
    string output = "";
    output += to_string(id) + ": " + restaurant_name + " " + to_string(table_id) + " ";
    output += to_string(time.first) + "-" + to_string(time.second);
    for (auto f : foods)
        output += " " + f.first + "(" + to_string(f.second) + ")";
    output += "\n";
    return output;
}

string Reservation::getInfo()
{
    string output = "";
    output += "Reserve ID: " + to_string(id) + "\n";
    output += "Table " + to_string(table_id) + " for " + to_string(time.first) + " to " + to_string(time.second);
    output += " in " + restaurant_name + "\n";
    output += "Price: " + to_string(bill) + "\n";
    return output;
}

string Reservation::getTime()
{
    return "(" + to_string(time.first) + "-" + to_string(time.second) + ")";
}

bool Reservation::checkTimeInterference(time_period time_limit, bool shoud_be_in_period)
{
    if (shoud_be_in_period)
        return (time.second > time_limit.second) || (time.first < time_limit.first);
    else
        return (time.first < time_limit.second) && (time.second > time_limit.first);
}

bool Reservation::checkTimeInterference(shared_ptr<Reservation> other_reserve, bool shoud_be_in_period)
{
    if (shoud_be_in_period)
        return (time.second > other_reserve->time.second) || (time.first < other_reserve->time.first);
    else
        return (time.first < other_reserve->time.second) && (time.second > other_reserve->time.first);
}

bool Reservation::operator<(const Reservation& other)
{
    return time.first < other.time.first;
}
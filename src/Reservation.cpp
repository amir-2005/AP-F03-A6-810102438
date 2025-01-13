#include "Reservation.hpp"

Reservation::Reservation(string _restaurant_name, int _table_id, time_period _time, map<food, int> _foods)
{
    restaurant_name = _restaurant_name;
    table_id = _table_id;
    time = _time;
    foods = _foods;
}

vector<string> Reservation::getTotalInfo()
{
    vector<string> output;
     + ": " + restaurant_name + " " + to_string(table_id) + " ";
    output.push_back(to_string(id));
    output.push_back(restaurant_name);
    output.push_back(to_string(table_id));
    output.push_back(to_string(time.first));
    output.push_back(to_string(time.second));

    string food_list;
    for (auto f : foods)
        food_list += f.first + "(" + to_string(f.second) + ") ";
    
    output.push_back(food_list);
    output.push_back(to_string(bill));
    output.push_back(to_string(bill - getTotalDiscount()));

    return output;
}

string Reservation::getInfo()
{
    string output = "";
    output += RESERVATION_INFO_ID + ": " + to_string(id) + "\n";
    output += RESERVATION_INFO_TABLE + " " + to_string(table_id) + " for " + to_string(time.first) + " to " + to_string(time.second);
    output += " in " + restaurant_name + "\n";
    output += RESERVATION_INFO_ORIGINAL_PRICE + ": " + to_string(bill) + "\n";
    output += RESERVATION_INFO_ORDER_DISCOUNT + ": " + to_string(order_discount) + "\n";
    output += RESERVATION_INFO_FOOD_DISCOUNT + ": " + to_string(food_discount) + "\n";
    output += RESERVATION_INFO_FIRST_DISCOUNT + ": " + to_string(first_discount) + "\n";
    output += RESERVATION_INFO_TOTAL_DISCOUNT + ": " + to_string(getTotalDiscount()) + "\n";
    output += RESERVATION_INFO_TOTAL_PRICE + ": " + to_string(bill - getTotalDiscount()) + "\n";
    return output;
}

string Reservation::getTime()
{
    return "(" + to_string(time.first) + "-" + to_string(time.second) + ")";
}

bool Reservation::checkTimeInterference(time_period time_limit, bool shoud_be_in_period)
{
    time_period time_copy = time;

    if (time_limit.first > time_limit.second)
        time_limit.second += FULL_DAY_TIME;

    if (time_copy.first > time_copy.second)
        time_copy.second += FULL_DAY_TIME;

    if (shoud_be_in_period)
        return (time_copy.second > time_limit.second) || (time_copy.first < time_limit.first);
    else
        return (time_copy.first < time_limit.second) && (time_copy.second > time_limit.first);
}

bool Reservation::checkTimeInterference(shared_ptr<Reservation> other_reserve, bool shoud_be_in_period)
{
    time_period time_copy = time;

    if (other_reserve->time.first > other_reserve->time.second)
        other_reserve->time.second += FULL_DAY_TIME;

    if (time_copy.first > time_copy.second)
        time_copy.second += FULL_DAY_TIME;
    
    if (shoud_be_in_period)
        return (time.second > other_reserve->time.second) || (time.first < other_reserve->time.first);
    else
        return (time.first < other_reserve->time.second) && (time.second > other_reserve->time.first);
}

bool Reservation::operator<(const Reservation &other)
{
    return time.first < other.time.first;
}

int Reservation::getTotalDiscount()
{
    return first_discount + order_discount + food_discount;
}
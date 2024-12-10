#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include "libraries.hpp"
#include "constants.hpp"

class Reservation
{
public:
    Reservation(string _restaurant_name, time_period _time, vector<food> _foods);
    string showInformation();
private:
    string restaurant_name;
    time_period time;
    vector<food> foods;
};

#endif
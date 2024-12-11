#ifndef RESERVATION_HPP
#define RESERVATION_HPP

class Reservation;

#include "libraries.hpp"
#include "constants.hpp"
#include "User.hpp"

class Reservation
{
public:
    Reservation(string _restaurant_name, time_period _time, vector<food> _foods);
    string getInfo();
    

private:
    shared_ptr<User> user;
    string restaurant_name;
    time_period time;
    vector<food> foods;
};

#endif
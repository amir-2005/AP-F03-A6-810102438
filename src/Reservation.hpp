#ifndef RESERVATION_HPP
#define RESERVATION_HPP

class Reservation;

#include "libraries.hpp"
#include "constants.hpp"
#include "User.hpp"

class Reservation
{
public:
    Reservation(int _id, string _restaurant_name, time_period _time, map<food, int> _foods, shared_ptr<User> _user);
    string getInfo();
    string restaurant_name;
    int id;

private:
    shared_ptr<User> user;
    time_period time;
    map<food, int> foods;
    int table_id;
};

#endif
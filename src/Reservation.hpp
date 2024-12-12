#ifndef RESERVATION_HPP
#define RESERVATION_HPP

class Reservation;

#include "libraries.hpp"
#include "constants.hpp"
#include "User.hpp"

using namespace std;

class Reservation
{
public:
    Reservation(string _restaurant_name, int _table_id, time_period _time, map<food, int> _foods, shared_ptr<User> _user);
    string getTotalInfo();
    string getInfo();
    string getTime();
    bool checkTimeInterference(time_period time_limit, bool shoud_be_in = false);
    string restaurant_name;
    map<food, int> foods;
    int id;
    int bill;

private:
    time_period time;
    shared_ptr<User> user;
    int table_id;
};

#endif
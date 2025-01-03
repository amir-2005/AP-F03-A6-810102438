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
    Reservation(string _restaurant_name, int _table_id, time_period _time, map<food, int> _foods);
    string getTotalInfo();
    string getInfo();
    string getTime();
    bool checkTimeInterference(time_period time_limit, bool shoud_be_in_period);
    bool checkTimeInterference(shared_ptr<Reservation> other_reserve, bool shoud_be_in_period);
    bool operator<(const Reservation& other);
    void setDiscount(int _discount) {discount += _discount;}
    string restaurant_name;
    map<food, int> foods;
    int id;
    int bill;

private:
    time_period time;
    int table_id;
    int discount = 0;
};

#endif
#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

class Restaurant;

#include "libraries.hpp"
#include "constants.hpp"
#include "Reservation.hpp"

using namespace std;

class Restaurant
{
public:
    Restaurant(string _name, int tabels_num, map<string, int> _menu, int open_time, int close_time);
    void reserveTable(Reservation reserve, int table_id);
    void deleteReservation(Reservation reserve);
    string getInfo();
    string name;

private:
    map<food, int> menu;
    vector<shared_ptr<Reservation>> tables;
    time_period working_time;
};

#endif
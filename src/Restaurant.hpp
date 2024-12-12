#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

class Restaurant;

#include "libraries.hpp"
#include "constants.hpp"
#include "Reservation.hpp"
#include "Exceptions.hpp"

using namespace std;

class Restaurant
{
public:
    Restaurant(string _name, string district_name ,int tabels_num, map<string, int> _menu, int open_time, int close_time);
    void reserveTable(shared_ptr<Reservation> reserve, int table_id);
    void deleteReservation(Reservation reserve);
    string getInfo();
    string name;
    string district_name;
    vector<vector<shared_ptr<Reservation>>> tables;
    bool isInMenu(const food &name);

private:
    map<food, int> menu;
    time_period working_time;
    int last_reserve_id = 0;
};

#endif
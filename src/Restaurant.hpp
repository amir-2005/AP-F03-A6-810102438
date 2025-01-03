#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

class Restaurant;

#include "libraries.hpp"
#include "constants.hpp"
#include "Discount.hpp"
#include "Reservation.hpp"
#include "Exceptions.hpp"

using namespace std;

class Restaurant
{
public:
    Restaurant(string _name, string district_name ,int tabels_num, map<string, int> _menu, int open_time, int close_time);
    int reserveTable(shared_ptr<Reservation> reserve, int table_id);
    void removeReservation(int reserve_id);
    string getInfo();
    string name;
    string district_name;
    vector<vector<shared_ptr<Reservation>>> tables;

    int getPriceInMenu(const food &name);
    list<shared_ptr<Discount>> discounts;

private:
    map<food, int> menu;
    time_period working_time;
    int last_reserve_id = 0;
    
};

#endif
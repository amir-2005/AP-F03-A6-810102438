#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

class Restaurant;

#include "libraries.hpp"
#include "constants.hpp"
#include "Reservation.hpp"
#include "district.hpp"

using namespace std;

class Restaurant
{
public:
    Restaurant(string _name, District _district, int tabels_num, map<string, int> _menu, int open_time, int close_time);
    void reserveTable(Reservation reserve, int table_id);
    void deleteReservation(Reservation reserve);
    string getInformation();

private:
    string name;
    District district;
    map<food, int> menu;
    vector<shared_ptr<Reservation>> tables;
    time_period open_time;
};

#endif
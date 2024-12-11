#ifndef UTASTE_HPP
#define UTASTE_HPP

#include "libraries.hpp"
#include "constants.hpp"
#include "User.hpp"
#include "Restaurant.hpp"

class UTaste
{
public:
    UTaste();
    void loadData(string path_to_restaurants, string path_to_districts);
    void login(string username, string password);
    void logout();
    string getDistrictsInfo(string district_name);
    void setUserDistrict();
    string getRestaurantsInfo(food name);
    void setReservation(string restaurant_name, int table_id, time_period reserve_time, vector<food> foods);
    void showReservations(string restaurant_name, int reserve_id);
    void deleteReservation(string restaurant_name, int reserve_id);

private:
    User current_user;
    list<shared_ptr<User>> users;
    list<shared_ptr<Restaurant>> rests;
    map<int, shared_ptr<Reservation>> reservs;
    vector<shared_ptr<distric>> districts;
};

#endif
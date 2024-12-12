#ifndef UTASTE_HPP
#define UTASTE_HPP

#include "libraries.hpp"
#include "constants.hpp"
#include "User.hpp"
#include "Restaurant.hpp"
#include "Exceptions.hpp"

class UTaste
{
public:
    UTaste(string path_to_restaurants, string path_to_districts);
    void loadDistrictsData(string path_to_districts);
    void loadRestaurantData(string path_to_restaurants);
    void signUp(string username, string password);
    void login(string username, string password);
    void logout();
    string getDistrictsInfo(string district_name);
    void setUserDistrict(string district_name);
    string getRestaurantsList(food food);
    string getRestaurantInfo(string restaurant_name);
    string setReservation(string restaurant_name, int table_id, time_period reserve_time, map<food, int> foods);
    string showReservations(string restaurant_name, int reserve_id);
    void deleteReservation(string restaurant_name, int reserve_id);

    void test();

private:
    shared_ptr<User> current_user = nullptr;
    list<shared_ptr<User>> users;
    list<shared_ptr<Restaurant>> rests;
    vector<shared_ptr<District>> districts;
    bool logged_in = false;

    void restaurantBFS(shared_ptr<District> district, vector<string>& visited, string& output, food& food);
    
};

#endif
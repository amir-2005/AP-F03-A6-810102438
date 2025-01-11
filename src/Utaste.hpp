#ifndef UTASTE_HPP
#define UTASTE_HPP

class UTaste;

#include "libraries.hpp"
#include "constants.hpp"
#include "User.hpp"
#include "Restaurant.hpp"
#include "Discount.hpp"
#include "Exceptions.hpp"

class UTaste
{
public:
    UTaste(string path_to_restaurants, string path_to_districts, string path_to_discounts);
    void loadDistrictsData(string path_to_districts);
    void loadRestaurantData(string path_to_restaurants);
    void loadDiscountsData(string path_to_discounts);
    void signUp(string username, string password);
    void login(string username, string password);
    void logout();
    string getDistrictsInfo(string district_name);
    void setUserDistrict(string district_name);
    string getRestaurantsList(food food);
    string getRestaurantInfo(string restaurant_name);
    string setReservation(string restaurant_name, int table_id, time_period reserve_time, map<food, int> foods);
    string showReservations(string restaurant_name, int reserve_id);
    string showBudget();
    void increaseBudget(int amount);
    void deleteReservation(string restaurant_name, int reserve_id);
    shared_ptr<User> current_user = nullptr;

private:
    list<shared_ptr<User>> users;
    vector<shared_ptr<Restaurant>> rests;
    vector<shared_ptr<District>> districts;
    bool logged_in = false;

    void restaurantBFS(shared_ptr<District> district, vector<string>& visited, list<shared_ptr<District>> queue, string& output, food& food);
    
};

#endif
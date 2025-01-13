#ifndef User_HPP
#define User_HPP

class User;

#include "libraries.hpp"
#include "Reservation.hpp"
#include "constants.hpp"
#include "district.hpp"
using namespace std;

class User
{
public:
    User(string _name, string _password);
    void setDistrict(shared_ptr<District> current_distric);
    void addReservation(shared_ptr<Reservation> reservation);
    void removeReservation(string restaurnat_name, int reserve_id);
    bool canReserveInThisTime(time_period new_time);
    bool hasThisReservation(string restaurant_name, int reserve_id);
    vector<vector<string>> getReservationsInfo(string restaurant_name, int id);
    string getName() { return name; };
    string getPassword() { return password; };
    shared_ptr<District> distric;
    int budget = 0;

private:
    list<shared_ptr<Reservation>> reservs;
    string name;
    string password;
};

#endif
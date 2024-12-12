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
    void removeReservation(shared_ptr<Reservation> reservation);
    bool canReserveInThisTime(time_period new_time);
    string getReservationsInfo(string restaurant_name, int id);
    string getName() { return name; };
    string getPassword() { return password; };
    shared_ptr<District> distric;

private:
    list<shared_ptr<Reservation>> reservs;
    string name;
    string password;
    void sortReservation();
};

#endif
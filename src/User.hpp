#ifndef User_HPP
#define User_HPP

#include "libraries.hpp"
#include "Reservation.hpp"
#include "constants.hpp"
#include "district.hpp"
using namespace std;

class User
{
public:
    User(string _name, string _password);
    void setDistrict(District current_distric);
    void addReservation(Reservation& reservation);
    void removeReservation(Reservation& reservation);
    list<shared_ptr<Reservation>> getReservations();

private:
    string name;
    string password;
    list<shared_ptr<Reservation>> reservs;
    District distric;

};

#endif
#include "User.hpp"

User::User(string _name, string _password)
{
    name = name;
    password = password;
}

void User::setDistrict(shared_ptr<District> current_district)
{
    distric = current_district;
}

void User::addReservation(shared_ptr<Reservation> reservation)
{
    reservs.push_back(reservation);
}

void User::removeReservation(shared_ptr<Reservation> reservation)
{
    reservs.remove(reservation);
}

string User::getReservationInfo(string restaurant_name, int id)
{
    string output = "";
    for (auto r : reservs)
        if (restaurant_name.empty() || r->restaurant_name == restaurant_name)
            if (id == 0 || r->id == id)
            {
                output += r->getInfo() + "\n";
            }

    return output;
}
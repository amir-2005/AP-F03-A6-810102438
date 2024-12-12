#include "User.hpp"

User::User(string _name, string _password)
{
    name = _name;
    password = _password;
}

void User::setDistrict(shared_ptr<District> current_district)
{
    distric = current_district;
}

void User::addReservation(shared_ptr<Reservation> reservation)
{
    reservs.push_back(reservation); 
}

bool User::canReserveInThisTime(time_period new_time)
{
    for (auto r:reservs)
        if (r->checkTimeInterference(new_time , false))
            return false;

    return true;
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
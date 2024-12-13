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
    if (new_time.first < 1 || new_time.second > 24 || new_time.first >= new_time.second)
        return false;

    for (auto r : reservs)
        if (r->checkTimeInterference(new_time, false))
            return false;
    return true;
}

void User::removeReservation(string restaurnat_name, int reserve_id)
{
    for (auto r : reservs)
        if ((r->restaurant_name == restaurnat_name) && (r->id == reserve_id))
        {
            reservs.remove(r);
            return;
        }

    throw(NotFound(restaurnat_name + to_string(reserve_id) + MSG_NOT_FOUND));
}

string User::getReservationsInfo(string restaurant_name, int id)
{
    if (reservs.empty())
        throw(Empty(MSG_EMPTY_NO_RESERVATION));

    reservs.sort([](const shared_ptr<Reservation> &a, const shared_ptr<Reservation> &b)
                 { return *a < *b; });
                 
    string output = "";
    for (auto r : reservs)
        if (restaurant_name.empty() || r->restaurant_name == restaurant_name)
            if (id == 0 || r->id == id)
                output += r->getTotalInfo();

    if (output.empty())
        throw(NotFound(restaurant_name + to_string(id) + MSG_NOT_FOUND));

    return output;
}

bool User::hasThisReservation(string restaurant_name, int reserve_id)
{
    for (auto r : reservs)
        if ((r->restaurant_name == restaurant_name) && (r->id = reserve_id))
            return true;
    return false;
}
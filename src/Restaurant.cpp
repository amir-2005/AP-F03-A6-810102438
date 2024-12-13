#include "Restaurant.hpp"

Restaurant::Restaurant(string _name, string _district_name, int tabels_num, map<string, int> _menu, int open_time, int close_time)
{
    name = _name;
    district_name = _district_name;
    menu = _menu;
    tables.resize(tabels_num);
    working_time = make_pair(open_time, close_time);
}

void Restaurant::reserveTable(shared_ptr<Reservation> reserve, int table_id)
{
    // Assuming that table_id start at 0
    if (table_id > tables.size())
        throw(NotFound(MSG_NOT_FOUND_TABLE_ID));

    for (auto f : reserve->foods)
        if (menu.find(f.first) == menu.end())
            throw(NotFound(MSG_NOT_FOUND_FOOD));

    if (reserve->checkTimeInterference(working_time, true))
    {
        throw(PermissionDenied(MSG_PERMISSION_DENIED_RESERVE_TIME));
    }
    for (auto r : tables[table_id - 1])
        if (reserve->checkTimeInterference(r, false))
            throw(PermissionDenied(MSG_PERMISSION_DENIED_TABLE));
    int bill = 0;

    tables[table_id - 1].push_back(reserve);
    last_reserve_id++;
    reserve->id = last_reserve_id;

    for (auto f : reserve->foods)
        bill += menu[f.first] * f.second;

    reserve->setBill(bill);
}

bool Restaurant::isInMenu(const food &name)
{
    return (menu.find(name) != menu.end());
}

string Restaurant::getInfo()
{
    string output = "";
    output += "Name: " + name + "\n";
    output += "District: " + district_name + "\n";
    output += "Time: " + to_string(working_time.first) + "-" + to_string(working_time.second) + "\n";
    output += "Menu: ";
    for (auto item : menu)
        output += item.first + "(" + to_string(item.second) + "), ";
    output.erase(output.size() - 2);
    output += "\n";

    for (int i = 0; i < tables.size(); i++)
    {
        output += to_string(i + 1) + ": ";
        for (auto r : tables[i])
            output += r->getTime() + ", ";
        output.erase(output.size() - 2);
        output += "\n";
    }

    return output;
}

void Restaurant::removeReservation(int reserve_id)
{
    for (auto table:tables)
        for (auto r:table)
            if (r->id == reserve_id)
                table.erase(std::remove(table.begin(), table.end(), r), table.end());
    
    throw(NotFound(name + to_string(reserve_id) + MSG_NOT_FOUND));
}

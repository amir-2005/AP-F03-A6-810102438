#include "Restaurant.hpp"

Restaurant::Restaurant(string _name, int tabels_num, map<string, int> _menu, int open_time, int close_time)
{
    name = _name;
    menu = _menu;
    tables.resize(tabels_num);
    working_time = make_pair(open_time, close_time);
}

void Restaurant::reserveTable(shared_ptr<Reservation> reserve, int table_id)
{
    // Assuming that table_id start at 0
    if (table_id > tables.size())
        throw(NotFound("table id out of range"));

    for (auto f : reserve->foods)
        if (menu.find(f.first) == menu.end())
            throw(NotFound("food is not availble"));

    if (reserve->checkTimeInterference(working_time, true))
        throw(PermissionDenied("reserve time out of working hours"));

    for (auto r : tables[table_id - 1])
        if (reserve->checkTimeInterference(working_time, false))
            throw(PermissionDenied("table is reserved"));

    int bill=0;

    tables[table_id - 1].push_back(reserve);
    last_reserve_id ++;
    reserve->id = last_reserve_id;

    for (auto f : reserve->foods)
        bill += menu[f.first] * f.second;

    reserve->bill = bill;
}


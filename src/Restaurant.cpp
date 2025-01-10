#include "Restaurant.hpp"

Restaurant::Restaurant(string _name, string _district_name, int tabels_num, map<string, int> _menu, int open_time, int close_time)
{
    name = _name;
    district_name = _district_name;
    menu = _menu;
    tables.resize(tabels_num);
    working_time = make_pair(open_time, close_time);
}

int Restaurant::reserveTable(shared_ptr<Reservation> reserve, int table_id)
{
    if (table_id > tables.size() || table_id <= 0)
        throw(NotFound(MSG_NOT_FOUND_TABLE_ID));

    for (auto f : reserve->foods)
        if (menu.find(f.first) == menu.end())
            throw(NotFound(MSG_NOT_FOUND_FOOD));

    if (reserve->checkTimeInterference(working_time, true))
        throw(PermissionDenied(MSG_PERMISSION_DENIED_RESERVE_TIME));

    for (auto r : tables[table_id - 1])
        if (reserve->checkTimeInterference(r, false))
            throw(PermissionDenied(MSG_PERMISSION_DENIED_TABLE));

    int bill = 0;
    tables[table_id - 1].push_back(reserve);
    last_reserve_id++;
    reserve->id = last_reserve_id;

    for (auto f : reserve->foods)
        bill += menu[f.first] * f.second;

    reserve->bill = bill;

    for (auto discount : discounts)
        discount->apply(reserve);

    return bill - reserve->getTotalDiscount();
}

int Restaurant::getPriceInMenu(const food &name)
{
    if (menu.find(name) == menu.end())
        return 0;
    else
        return menu[name];
}

string Restaurant::getInfo()
{
    string output = "";
    output += RESTAURANT_INFO_NAME + ": " + name + "\n";
    output += RESTAURANT_INFO_DISTRICT + ": " + district_name + "\n";
    output += RESTAURANT_INFO_TIME + ": " + to_string(working_time.first) + "-" + to_string(working_time.second) + "\n";
    output += RESTAURANT_INFO_MENU + ": ";
    for (auto item : menu)
        output += item.first + "(" + to_string(item.second) + "), ";
    output.erase(output.size() - 2);
    output += "\n";

    for (int i = 0; i < tables.size(); i++)
    {
        output += to_string(i + 1) + ":";
        for (auto r : tables[i])
            output += " " + r->getTime() + ",";
        if (output.back() == ',')
            output.erase(output.size() - 1);
        output += "\n";
    }

    for (auto d : discounts)
        if (TotalPriceDiscount *TD = dynamic_cast<TotalPriceDiscount *>(d.get()))
        {
            output += RESTAURANT_INFO_ORDER_DISCOUNT + ": " + TD->info() + "\n";
            break;
        }

    if (FoodDiscount *FD = dynamic_cast<FoodDiscount*>(discounts.front().get()))
    {
        output += RESTAURANT_INFO_ITEM_DISCOUNT + ": ";
        for (auto d : discounts)
        if (FoodDiscount *FD = dynamic_cast<FoodDiscount *>(d.get()))
            output += FD->info() + ", ";
        output.erase(output.size() - 2);
        output += "\n";
    }

    for (auto d : discounts)
        if (FirstOrderDiscount *FOD = dynamic_cast<FirstOrderDiscount *>(d.get()))
        {
            output += RESTAURANT_INFO_FIRST_DISCOUNT + ": " + FOD->info() + "\n";
            break;
        }

    return output;
}

void Restaurant::removeReservation(int reserve_id)
{
    for (auto& table : tables)
        for (auto r : table)
            if (r->id == reserve_id)
            {
                table.erase(std::find(table.begin(), table.end(), r));
                return;
            }

    throw(NotFound(name + to_string(reserve_id) + MSG_NOT_FOUND));
}

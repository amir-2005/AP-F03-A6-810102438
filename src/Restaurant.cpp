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

map<string, vector<string>> Restaurant::getInfo()
{
    map<string, vector<string>> output;
    output[RESTAURANT_INFO_NAME] = vector<string>{name};
    output[RESTAURANT_INFO_DISTRICT] = vector<string>{district_name};
    output[RESTAURANT_INFO_TIME] = vector<string>{to_string(working_time.first) + "-" + to_string(working_time.second)};
    vector<string> menu_item, menu_price;

    for (auto item : menu)
    {
        menu_item.push_back(item.first);
        menu_price.push_back(to_string(item.second));
    }

    output[RESTAURANT_INFO_MENU_ITEM] = menu_item;
    output[RESTAURANT_INFO_MENU_PRICE] = menu_price;

    output[RESTAURANT_INFO_TABLE] = vector<string>{};
    for (int i = 0; i < tables.size(); i++)
    {
        string table_info = "";
        for (auto r : tables[i])
            table_info += " " + r->getTime() + ",";
        output[RESTAURANT_INFO_TABLE].push_back(table_info);
    }

    output[RESTAURANT_INFO_ORDER_DISCOUNT] = vector<string>{};
    for (auto d : discounts)
        if (TotalPriceDiscount *TD = dynamic_cast<TotalPriceDiscount *>(d.get()))
        {
            output[RESTAURANT_INFO_ORDER_DISCOUNT].push_back(TD->info());
            break;
        }

    output[RESTAURANT_INFO_ITEM_DISCOUNT] = vector<string>{};
    if (FoodDiscount *FD = dynamic_cast<FoodDiscount *>(discounts.front().get()))
    {
        for (auto d : discounts)
            if (FoodDiscount *FD = dynamic_cast<FoodDiscount *>(d.get()))
                output[RESTAURANT_INFO_ITEM_DISCOUNT].push_back(FD->info());
    }

    output[RESTAURANT_INFO_FIRST_DISCOUNT] = vector<string>{};
    for (auto d : discounts)
        if (FirstOrderDiscount *FOD = dynamic_cast<FirstOrderDiscount *>(d.get()))
        {
            output[RESTAURANT_INFO_FIRST_DISCOUNT].push_back(FOD->info());
            break;
        }

    return output;
}

void Restaurant::removeReservation(int reserve_id)
{
    for (auto &table : tables)
        for (auto r : table)
            if (r->id == reserve_id)
            {
                table.erase(std::find(table.begin(), table.end(), r));
                return;
            }

    throw(NotFound(name + to_string(reserve_id) + MSG_NOT_FOUND));
}

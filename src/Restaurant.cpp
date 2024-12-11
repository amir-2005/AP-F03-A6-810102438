#include "Restaurant.hpp"

Restaurant::Restaurant(string _name, int tabels_num, map<string, int> _menu, int open_time, int close_time)
{
    name = _name;
    menu = _menu;
    tables.resize(tabels_num);
    working_time = make_pair(open_time, close_time);
}
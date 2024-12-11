#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include "libraries.hpp"
#include "Restaurant.hpp"
using namespace std;

struct District
{
    District(string _name) : name(_name) {};
    string name;
    vector<shared_ptr<Restaurant>> rests;
    vector<shared_ptr<District>> neighbors;
};


#endif
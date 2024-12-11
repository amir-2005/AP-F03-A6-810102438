#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include "libraries.hpp"
// #include "Restaurant.hpp"
using namespace std;


typedef struct distric  
{
    string name;
    vector<shared_ptr<distric>> neighbors;
    // vector<shared_ptr<Restaurant>> rests;

} District;


#endif
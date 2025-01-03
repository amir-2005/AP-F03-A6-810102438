#ifndef DISCOUNT_HPP
#define DISCOUNT_HPP

#include "libraries.hpp"
#include "Reservation.hpp"
using namespace std;


class Discount
{
public:
    Discount(string _type, int _value) : value(_value), type(_type) {}
    virtual void apply(shared_ptr<Reservation> reserve) = 0;

protected:
    int value;
    string type;
};


class FirstOrderDiscount : public Discount
{
public:
    FirstOrderDiscount(string type, int value) : Discount(type, value) {}
    void apply(shared_ptr<Reservation> reserve);    
};


class TotalPriceDiscount : public Discount
{
public:
    TotalPriceDiscount(string type, int value, int min) : Discount(type, value), min_value(min) {}
    void apply(shared_ptr<Reservation> reserve);

private:
    int min_value;
};


class FoodDiscount : public Discount
{
public:
    FoodDiscount(string type, int value, food _name) : Discount(type, value), name(_name) {}
    void apply(shared_ptr<Reservation> reserve);

private:
    food name;
};

#endif
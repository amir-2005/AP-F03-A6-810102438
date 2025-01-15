#include "Discount.hpp"

void FirstOrderDiscount::apply(shared_ptr<Reservation> reserve)
{
    if (type == TYPE_AMOUNT)
    {
        if ((reserve->bill - reserve->food_discount) > value)
            reserve->first_discount += value;
    }
    else
    {
        int discount_amount = reserve->bill * (float(value) / 100);
        if ((reserve->bill - reserve->food_discount) > discount_amount)
            reserve->first_discount += discount_amount;
    }
}

void TotalPriceDiscount::apply(shared_ptr<Reservation> reserve)
{
    if ((reserve->bill - reserve->first_discount - reserve->food_discount) < min_value)
        return;

    if (type == TYPE_AMOUNT)
        reserve->order_discount += value;
    else
    {
        int discount_amount = (reserve->bill - reserve->first_discount - reserve->food_discount) * (float(value) / 100);
        reserve->order_discount += discount_amount;
    }
}

void FoodDiscount::apply(shared_ptr<Reservation> reserve)
{
    for (auto item : reserve->foods)
        if (item.first == name)
        {
            if (type == TYPE_AMOUNT)
                reserve->food_discount += value * item.second;
            else
            {
                int discount_amount = food_price * (float(value) / 100);
                reserve->food_discount += discount_amount * item.second;
            }
        }
}

string FirstOrderDiscount::info()
{
    if (type == TYPE_PERCENTAGE)
        return to_string(value) + "%";
    else
        return to_string(value); + "T";
}

string TotalPriceDiscount::info()
{
    if (type == TYPE_PERCENTAGE)
        return to_string(value) + "%" + " off on orders above " + to_string(min_value);
    else
        return to_string(value) + "T off on orders above " + to_string(min_value);
}

string FoodDiscount::info()
{
    string suffix = type == TYPE_PERCENTAGE ? "\% off" : "T off";
    return name + ": " + to_string(value) + suffix;
}
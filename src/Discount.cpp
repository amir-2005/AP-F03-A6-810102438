#include "Discount.hpp"

void FirstOrderDiscount::apply(shared_ptr<Reservation> reserve)
{
    if (type == TYPE_AMOUNT)
        reserve->first_discount += value;
    else
    {
        int discount_amount = reserve->bill * (float(value) / 100);
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
        int discount_amount = reserve->bill * (float(value) / 100);
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
    return type + ", " + to_string(value);
}

string TotalPriceDiscount::info()
{
    return type + ", " + to_string(min_value) + ", " + to_string(value);
}

string FoodDiscount::info()
{
    return name + "(" + type + ": " + to_string(value) + ")";
}
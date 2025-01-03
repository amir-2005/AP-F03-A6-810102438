#include "Discount.hpp"

void FirstOrderDiscount::apply(shared_ptr<Reservation> reserve)
{
    if (type == TYPE_AMOUNT)
        reserve->setDiscount(value);
    else
    {
        int discount_amount = reserve->bill * (float)(value / 100);
        reserve->setDiscount(discount_amount);
    }
}

void TotalPriceDiscount::apply(shared_ptr<Reservation> reserve)
{
    if (reserve->bill < min_value)
        return;

    if (type == TYPE_AMOUNT)
        reserve->setDiscount(value);
    else
    {
        int discount_amount = reserve->bill * (float)(value / 100);
        reserve->setDiscount(discount_amount);
    }
}

void FoodDiscount::apply(shared_ptr<Reservation> reserve)
{
    for (auto item : reserve->foods)
        if (item.first == name)
        {
            if (type == TYPE_AMOUNT)
                reserve->setDiscount(value);
            else
            {
                int discount_amount = item.second * (float)(value / 100);
                reserve->setDiscount(discount_amount);
            }
        }
}

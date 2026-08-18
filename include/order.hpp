#pragma once

#include <string>
#include <stdexcept>

enum class Side {
    BUY,
    SELL
};

struct Order
{
    /* data */
    std::string id;
    Side side;
    double price;
    int quantity;
    int time;

    Order(std::string id, Side side, double price, int quantity)
        : id(id), 
          side(side), 
          price(price), 
          quantity(quantity) 
    {
        if (id.empty()) {
            throw std::invalid_argument("ID must have a value");
        }

        if (price <= 0.0) {
            throw std::invalid_argument("Price must be greater than 0");
        }

        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be greater than 0");
        }

        if (time < 0) {
            throw std::invalid_argument("Time must be positive");
        }
    }

};

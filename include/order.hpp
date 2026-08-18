#pragma once

#include <string>
#include <stdexcept>

struct Order
{
    /* data */
    std::string id;
    std::string side;
    double price;
    int quantity;

    Order(std::string id, std::string side, double price, int quantity)
        : id(id), 
          side(side), 
          price(price), 
          quantity(quantity) 
    {
        if (id.empty()) {
            throw std::invalid_argument("ID must have a value");
        }

        if (side != "BUY" && side != "SELL") {
            throw std::invalid_argument("Side must be BUY or SELL");
        }

        if (price <= 0.0) {
            throw std::invalid_argument("Price must be greater than 0");
        }

        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be greater than 0");
        }
    }

};

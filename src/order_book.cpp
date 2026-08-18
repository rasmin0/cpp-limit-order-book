#include "order_book.hpp"
#include <stdexcept>
#include <string>



void OrderBook::addOrder(Order order)
{
    std::string id = order.id;
    Side side = order.side;
    double price = order.price;
    OrderLocation orderLocation;
    orderLocation.price = price;
    orderLocation.side = side;

    if (activeIDs.find(id) != activeIDs.end()) {
        throw std::invalid_argument("ID already exists");
    }
    

    if (side == Side::BUY) {
        if (buyOrders.find(price) == buyOrders.end()) {
            buyOrders[price] = std::deque<Order>{};
        }
        buyOrders[price].push_back(order);
    } else {
        if (sellOrders.find(price) == sellOrders.end()) {
            sellOrders[price] = std::deque<Order>{};
        }
        sellOrders[price].push_back(order);
    }
    activeIDs[id] = orderLocation;
}

void OrderBook::cancelOrder(const std::string &id)
{
    if (activeIDs.find(id) == activeIDs.end()) {
        throw std::invalid_argument("ID doesn't exist");
    }

    double price = activeIDs[id].price;
    Side side = activeIDs[id].side;
    activeIDs.erase(id);

    if (side == Side::BUY) {
        for (unsigned int i = 0; i < buyOrders[price].size(); ++i) {
            if (buyOrders[price][i].id == id) {
                buyOrders[price].erase(buyOrders[price].begin() + i);
                break;
            }
        }

    } else {
        for (unsigned int i = 0; i < sellOrders[price].size(); ++i) {
            if (sellOrders[price][i].id == id) {
                sellOrders[price].erase(sellOrders[price].begin() + i);
                break;
            }
        }
    }
}

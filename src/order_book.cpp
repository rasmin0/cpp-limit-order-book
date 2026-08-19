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
    order.time = nextTime;

    if (side == Side::BUY) {
        buyOrders[price].push_back(order);
    } else {
        sellOrders[price].push_back(order);
    }
    activeIDs[id] = orderLocation;
    nextTime++;
}

void OrderBook::cancelOrder(const std::string &id)
{
    if (activeIDs.find(id) == activeIDs.end()) {
        throw std::invalid_argument("ID doesn't exist");
    }

    double price = activeIDs[id].price;
    Side side = activeIDs[id].side;

    if (side == Side::BUY) {
        for (std::size_t i = 0; i < buyOrders[price].size(); ++i) {
            if (buyOrders[price][i].id == id) {
                buyOrders[price].erase(buyOrders[price].begin() + i);
                if (buyOrders[price].empty()) {
                    buyOrders.erase(price);
                }
                break;
            }
        }

    } else {
        for (std::size_t i = 0; i < sellOrders[price].size(); ++i) {
            if (sellOrders[price][i].id == id) {
                sellOrders[price].erase(sellOrders[price].begin() + i);
                if (sellOrders[price].empty()) {
                    sellOrders.erase(price);
                }
                break;
            }
        }
    }
    activeIDs.erase(id);
}
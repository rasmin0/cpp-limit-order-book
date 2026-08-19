#pragma once

#include "order.hpp"
#include <map>
#include <deque>
#include <string>
#include <unordered_map>
#include <functional>

struct OrderLocation {
    Side side;
    double price;
};

class OrderBook {
private:
    std::map<double, std::deque<Order>, std::greater<double>> buyOrders;
    std::map<double, std::deque<Order>> sellOrders;
    std::unordered_map<std::string, OrderLocation> activeIDs;
    std::size_t nextTime = 0;

public:
    // submit/add order
    // cancel order
    void addOrder(Order order);
    void cancelOrder(const std::string& id);
};

#pragma once

#include "order.hpp"
#include <map>
#include <deque>
#include <set>
#include <string>
#include <unordered_set>

struct OrderLocation {
    Side side;
    double price;
};

class OrderBook {
private:
    std::map<double, std::deque<Order>, std::greater<double>> buyOrders;
    std::map<double, std::deque<Order>> sellOrders;
    std::unordered_map<std::string, OrderLocation> activeIDs;

public:
    // submit/add order
    // cancel order
    
};

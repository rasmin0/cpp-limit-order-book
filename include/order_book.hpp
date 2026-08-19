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
    std::vector<Trade> tradeHistory;

public:
    // submit/add order
    // cancel order
    void addOrder(Order order);
    void cancelOrder(const std::string& id);
    void matchBuy(Order& order);
    void matchSell(Order& order);
    const std::vector<Trade>& getTradeHistory() const;
    bool isActive(const std::string& id) const;
};

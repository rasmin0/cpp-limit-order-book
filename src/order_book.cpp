#include "order_book.hpp"
#include <algorithm>
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
        matchBuy(order);
        if (order.quantity == 0) {
            return;
        }
        buyOrders[price].push_back(order);
    } else {
        matchSell(order);
        if (order.quantity == 0) {
            return;
        }
        sellOrders[price].push_back(order);
    }
    order.time = nextTime;
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

void OrderBook::matchBuy(Order &order)
{
    if (order.quantity == 0 || sellOrders.empty()) {
        return;
    }

    auto it = sellOrders.begin();

    Order& bestSell = it->second.front();

    if (order.price >= bestSell.price) {
        Trade trade;
        int tradeQuantity = std::min(order.quantity, bestSell.quantity);
        order.quantity -= tradeQuantity;
        bestSell.quantity -= tradeQuantity;
        trade.buyerID = order.id;
        trade.sellerID = bestSell.id;
        trade.price = bestSell.price;
        trade.quantity = tradeQuantity;
        tradeHistory.push_back(trade);

        if (order.quantity > 0) {
            activeIDs.erase(bestSell.id);
            matchBuy(order);
        } else {
            return;
        }
    } else {
        return;
    }
}

void OrderBook::matchSell(Order &order)
{
    if (order.quantity == 0 || buyOrders.empty()) {
        return;
    }

    auto it = buyOrders.begin();

    Order& bestBuy = it->second.front();

    if (order.price >= bestBuy.price) {
        Trade trade;
        int tradeQuantity = std::min(order.quantity, bestBuy.quantity);
        order.quantity -= tradeQuantity;
        bestBuy.quantity -= tradeQuantity;
        trade.buyerID = order.id;
        trade.sellerID = bestBuy.id;
        trade.price = bestBuy.price;
        trade.quantity = tradeQuantity;
        tradeHistory.push_back(trade);

        if (order.quantity > 0) {
            activeIDs.erase(bestBuy.id);
            matchSell(order);
        } else {
            return;
        }
    } else {
        return;
    }
}

const std::vector<Trade> &OrderBook::getTradeHistory() const
{
    return tradeHistory;
}

bool OrderBook::isActive(const std::string &id) const
{
    return activeIDs.find(id) != activeIDs.end();
}

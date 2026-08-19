#include <gtest/gtest.h>
#include "order_book.hpp"
#include <stdexcept>

// ORDER BOOK TESTS
// ---------------------------------------------------------------------------------------------

TEST(OrderBookTest, AddValidBuyOrder) {
    OrderBook book;

    Order order("123", Side::BUY, 100.0, 10);

    EXPECT_NO_THROW(book.addOrder(order));
}

TEST(OrderBookTest, AddValidSellOrder) {
    OrderBook book;

    Order order("123", Side::SELL, 100.0, 10);

    EXPECT_NO_THROW(book.addOrder(order));
}

TEST(OrderBookTest, AddDuplicateBuyOrder) {
    OrderBook book;

    Order order1("123", Side::BUY, 100.0, 10);
    Order order2("123", Side::BUY, 100.0, 10);

    book.addOrder(order1);

    EXPECT_THROW(book.addOrder(order2), std::invalid_argument);
}

TEST(OrderBookTest, AddDuplicateSellOrder) {
    OrderBook book;

    Order order1("123", Side::SELL, 100.0, 10);
    Order order2("123", Side::SELL, 100.0, 10);

    book.addOrder(order1);

    EXPECT_THROW(book.addOrder(order2), std::invalid_argument);
}

TEST(OrderBookTest, AddDuplicateBuySellOrder) {
    OrderBook book;

    Order order1("123", Side::BUY, 100.0, 10);
    Order order2("123", Side::SELL, 100.0, 10);

    book.addOrder(order1);

    EXPECT_THROW(book.addOrder(order2), std::invalid_argument);
}

TEST(OrderBookTest, CancelValidBuyOrder) {
    OrderBook book;

    Order order("123", Side::BUY, 100.0, 10);

    book.addOrder(order);

    EXPECT_NO_THROW(book.cancelOrder("123"));
}

TEST(OrderBookTest, CancelValidSellOrder) {
    OrderBook book;

    Order order("123", Side::SELL, 100.0, 10);

    book.addOrder(order);

    EXPECT_NO_THROW(book.cancelOrder("123"));
}

TEST(OrderBookTest, CancelInvalidOrder) {
    OrderBook book;

    EXPECT_THROW(book.cancelOrder("123"), std::invalid_argument);
}

TEST(OrderBookTest, ReuseCancelledBuyID) {
    OrderBook book;

    Order order1("123", Side::BUY, 100.0, 10);

    book.addOrder(order1);

    book.cancelOrder("123");

    Order order2("123", Side::BUY, 100.0, 10);

    EXPECT_NO_THROW(book.addOrder(order2));
}

TEST(OrderBookTest, ReuseCancelledSellID) {
    OrderBook book;

    Order order1("123", Side::SELL, 100.0, 10);

    book.addOrder(order1);

    book.cancelOrder("123");

    Order order2("123", Side::SELL, 100.0, 10);

    EXPECT_NO_THROW(book.addOrder(order2));
}
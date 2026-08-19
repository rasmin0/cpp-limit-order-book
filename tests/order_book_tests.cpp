#include <gtest/gtest.h>
#include "order_book.hpp"
#include "order.hpp"
#include <stdexcept>

// ORDER BOOK ADD ORDER TESTS
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

// ORDER BOOK CANCEL ORDER TESTS
// ---------------------------------------------------------------------------------------------

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

// ORDER BOOK MATCH BUY TESTS
// ---------------------------------------------------------------------------------------------

TEST(MatchBuyTest, MatchValidOrder) {

}

TEST(MatchBuyTest, EvenTrade) {
    OrderBook book;

    Order order1("123", Side::BUY, 100.0, 10);
    Order order2("1234", Side::SELL, 99.0, 10);

    book.addOrder(order2);
    book.addOrder(order1);

    const auto& trades = book.getTradeHistory();

    ASSERT_EQ(trades.size(), 1);
    EXPECT_EQ(trades[0].buyerID, "123");
    EXPECT_EQ(trades[0].sellerID, "1234");
    EXPECT_DOUBLE_EQ(trades[0].price, 99.0);
    EXPECT_EQ(trades[0].quantity, 10);
    EXPECT_FALSE(book.isActive("1234"));
    EXPECT_FALSE(book.isActive("123"));

}

TEST(MatchBuyTest, NoTrade) {
    OrderBook book;

    Order order1("123", Side::BUY, 100.0, 10);
    Order order2("1234", Side::SELL, 101.0, 10);

    book.addOrder(order2);
    book.addOrder(order1);

    const auto& trades = book.getTradeHistory();

    ASSERT_EQ(trades.size(), 0);
    EXPECT_TRUE(book.isActive("1234"));
    EXPECT_TRUE(book.isActive("123"));
}

TEST(MatchBuyTest, SellIsEmpty) {

}


TEST(MatchBuyTest, PartiallyFilledBuy) {

}

TEST(MatchBuyTest, PartiallyFilledSell) {

}

// ORDER BOOK MATCH SELL TESTS
// ---------------------------------------------------------------------------------------------


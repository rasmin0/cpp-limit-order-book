#include <gtest/gtest.h>
#include "order.hpp"

// ORDER TESTS
// ---------------------------------------------------------------------------------------------

TEST(OrderTest, ValidOrderStoresFields) {
    Order order("123", Side::BUY, 100.0, 5, 0);

    EXPECT_EQ(order.id, "123");
    EXPECT_EQ(order.side, Side::BUY);
    EXPECT_EQ(order.price, 100.0);
    EXPECT_EQ(order.quantity, 5);
    EXPECT_EQ(order.time, 0);
}


TEST(OrderTest, EmptyIDThrows) {
    EXPECT_THROW(
        Order("", Side::BUY, 100.0, 5, 0),
        std::invalid_argument
    );
}


TEST(OrderTest, ZeroPriceThrows) {
    EXPECT_THROW(
        Order("123", Side::BUY, 0.0, 5, 0),
        std::invalid_argument
    );
}



TEST(OrderTest, NegativePriceThrows) {
    EXPECT_THROW(
        Order("123", Side::BUY, -100.0, 5, 0),
        std::invalid_argument
    );
}


TEST(OrderTest, ZeroQuantityThrows) {
    EXPECT_THROW(
        Order("123", Side::BUY, 100.0, 0, 0),
        std::invalid_argument
    );
}


TEST(OrderTest, NegativeQuantityThrows) {
    EXPECT_THROW(
        Order("123", Side::BUY, 100.0, -5, 0),
        std::invalid_argument
    );
}


TEST(OrderTest, NegativeTimeThrows) {
    EXPECT_THROW(
        Order("123", Side::BUY, 100.0, 5, -1),
        std::invalid_argument
    );
}


#include <iostream>
#include <stdexcept>
#include "order.hpp"

int main() 
{
    // Test a valid order
    try {
        Order order("1234", Side::SELL, 14.0, 5, 0);

        std::cout << "Order created successfully\n";
        std::cout << "ID: " << order.id << '\n';
        std::cout << "Side: "
                  << (order.side == Side::BUY ? "BUY" : "SELL")
                  << '\n';
        std::cout << "Price: " << order.price << '\n';
        std::cout << "Quantity: " << order.quantity << '\n';
    }
    catch (const std::invalid_argument& error) {
        std::cerr << "Unexpected error: " << error.what() << '\n';
    }

    // Test an invalid order
    try {
        Order invalidOrder("5678", Side::BUY, -10.0, 5, -1);
        std::cerr << "Test failed: invalid order was created\n";
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Invalid-order test passed: "
                  << error.what() << '\n';
    }

    

    return 0;
}
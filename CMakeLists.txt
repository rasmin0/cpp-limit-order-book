set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.14)

project(cpp_limit_order_book)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(smoke_test
    tests/smoke_test.cpp
)

add_executable(order_book_tests
    tests/order_book_tests.cpp
)

add_executable(order_tests
    tests/order_tests.cpp
)

target_include_directories(smoke_test PRIVATE include)

target_include_directories(order_book_tests PRIVATE include)

target_include_directories(order_tests PRIVATE include)

target_link_libraries(smoke_test PRIVATE GTest::gtest_main)
target_link_libraries(order_book_tests PRIVATE GTest::gtest_main)
target_link_libraries(order_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(smoke_test)
gtest_discover_tests(order_book_tests)
gtest_discover_tests(order_tests)
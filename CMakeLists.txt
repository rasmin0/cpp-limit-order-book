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

target_include_directories(smoke_test PRIVATE include)

target_link_libraries(smoke_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(smoke_test)
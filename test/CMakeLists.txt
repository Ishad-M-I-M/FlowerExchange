cmake_minimum_required(VERSION 3.25)

project(FlowerExchangeTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main FlowerExchange)

target_compile_definitions(${PROJECT_NAME} PUBLIC TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
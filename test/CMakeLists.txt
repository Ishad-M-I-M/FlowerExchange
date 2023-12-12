cmake_minimum_required(VERSION 3.25)

project(FlowerExchangeTest)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE LIST_DIRECTORIES true *.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} gtest gtest_main FlowerExchange)

target_compile_definitions(${PROJECT_NAME} PUBLIC TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
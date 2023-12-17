cmake_minimum_required(VERSION 3.25)

project(FlowerExchangeTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main FlowerExchange)

target_compile_definitions(${PROJECT_NAME} PUBLIC TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

#file(GLOB_RECURSE CSV_FILES FILES_MATCHING "${CMAKE_CURRENT_SOURCE_DIR}/resources/temp/*.csv")
#
#if(NOT CSV_FILES)
#    message(STATUS "No CSV files found in ${CSV_DIRECTORY}")
#else()
#    add_custom_target(clean_files
#            COMMAND ${CMAKE_COMMAND} -E echo "cleaning ${TEMP_DIR}"
#            COMMAND ${CMAKE_COMMAND} -E rm ${CSV_FILES}
#            )
#    add_dependencies(${PROJECT_NAME} clean_files)
#endif()
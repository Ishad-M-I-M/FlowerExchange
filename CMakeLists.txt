cmake_minimum_required(VERSION 3.25)
project(FlowerExchange)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

set(SOURCES
        src/utils.h
        src/utils.cpp
        src/order_book.h
        src/order_book.cpp
        src/exchange_application.h
        src/exchange_application.cpp
        )
add_library(${PROJECT_NAME} ${SOURCES})
add_executable(${PROJECT_NAME}App main.cpp)
target_link_libraries(${PROJECT_NAME}App ${PROJECT_NAME})
add_subdirectory(test)

# Include google test
include(FetchContent)

FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    message("DEBUG build type is set.")
    include(CodeCoverage)
    append_coverage_compiler_flags_to_target(${PROJECT_NAME})
    setup_target_for_coverage_gcovr_xml(
            NAME coverage
            EXECUTABLE ${PROJECT_NAME}Test
            BASE_DIRECTORY "${PROJECT_SOURCE_DIR}/src"
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0 ")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()
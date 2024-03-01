cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
project(completesearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(completesearch src/main.cpp)

set(SOURCES
    src/game.h
    src/game.cpp)

target_sources(completesearch PRIVATE ${SOURCES})

enable_testing()
include(GoogleTest)
add_executable(game_test src/game_test.cpp)

target_link_libraries(
    game_test
    GTest::gtest_main
)

target_sources(game_test PRIVATE ${SOURCES})

gtest_discover_tests(game_test)

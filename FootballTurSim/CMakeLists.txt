
cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0048 NEW)


project(FootballTurSim)
project(TestFootballTurSim)

#for linux
find_package(PkgConfig)
#find_package(gtest REQUIRED)
pkg_search_module(GTEST REQUIRED gtest_main)
include_directories(${GTEST_INCLUDE_DIRS})

#for windows
#find_package(GTest CONFIG REQUIRED)
#find_package(gtest REQUIRED)
#pkg_search_module(GTEST REQUIRED gtest_main)
#include_directories(${GTEST_INCLUDE_DIRS})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MeanGoalPerGame.csv
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/MeanGoalPerGame.csv)

add_executable(FootballTurSim main.cpp)

add_executable(TestFootballTurSim tests.cpp)
#target_link_libraries(TestFootballTurSim gtest)
#target_link_libraries(TestFootballTurSim GTest::GTest)

#target_link_libraries(TestFootballTurSim PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
target_link_libraries(TestFootballTurSim ${GTEST_LDFLAGS})
target_compile_options(TestFootballTurSim PUBLIC ${GTEST_CFLAGS})


# include(CTest)
# add_test(FooTest.DoesXyz TestFootballTurSim)

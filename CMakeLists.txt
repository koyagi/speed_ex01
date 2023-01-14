cmake_minimum_required(VERSION 3.22)
project(speed CXX)

if (APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif(APPLE)

enable_testing()

add_executable(hello dealer.cpp)
target_compile_features(hello PRIVATE cxx_std_17)
set_target_properties(hello PROPERTIES CXX_EXTENTIONS OFF)
target_compile_options(hello PRIVATE -Wall -Werror -pedantic-errors -Weffc++)

find_package(GTest)
include(GoogleTest)
add_executable(test_dealer tests/test_dealer.cpp)
target_compile_features(test_dealer PRIVATE cxx_std_17)
set_target_properties(test_dealer PROPERTIES CXX_EXTENTIONS OFF)
target_compile_options(test_dealer PRIVATE -Wall -pedantic-errors -Weffc++ -pthread)
# target_link_libraries(test_dealer GTest::GTest GTest::Main)
target_link_libraries(test_dealer GTest::Main GTest::GTest -ldl -pthread)
# target_link_options(test_dealer PRIVATE -lgtest_main -lgtest)

gtest_discover_tests(test_dealer)
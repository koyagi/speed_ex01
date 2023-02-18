cmake_minimum_required(VERSION 3.22)
project(speed CXX)

if (APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif(APPLE)

enable_testing()

add_executable(hello dealer.cpp)
target_compile_features(hello PRIVATE cxx_std_17)
set_target_properties(hello PROPERTIES CXX_EXTENTIONS OFF)
target_compile_options(hello PRIVATE -Wall -Werror -Wextra -pedantic-errors -Weffc++)

find_package(GTest)
include(GoogleTest)

set(test_targets test_dealer;test_cardoperation)
foreach(test IN LISTS test_targets)
  add_executable(${test} tests/${test}.cpp)
  target_compile_features(${test} PRIVATE cxx_std_17)
  set_target_properties(${test} PROPERTIES CXX_EXTENTIONS OFF)
  target_compile_options(${test} PRIVATE -Wall -Wextra -pedantic-errors -Weffc++ -pthread)
  # target_link_libraries(${test} GTest::GTest GTest::Main)
  target_link_libraries(${test} GTest::Main GTest::GTest -ldl -pthread)
  # target_link_options(${test} PRIVATE -lgtest_main -lgtest)
endforeach()

gtest_discover_tests(test_dealer)
cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME crypto)
project(crypto)
add_subdirectory(lib/gtest-1.7.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(src)
enable_testing()
add_test(TestSuite src/TestSuite)

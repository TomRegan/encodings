################################
# Binaries and Libraries
################################
set(SOURCE_FILES
  encodings.cc
)
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
add_library(encodings_lib ${SOURCE_FILES})

################################
# Tests
################################
set(TEST_FILES
  test_encodings.cc
)
add_executable(TestSuite ${TEST_FILES})
target_link_libraries(TestSuite gtest gtest_main)
target_link_libraries(TestSuite encodings_lib)

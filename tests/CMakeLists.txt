include(FetchContent)

FetchContent_Declare(
  googletest 
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 #release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(string_utils_tests string_utils_unittests.cpp)

target_link_libraries(string_utils_tests
 PRIVATE
  GTest::GTest
  string_utils
)

include(GoogleTest)
gtest_discover_tests(string_utils_tests)
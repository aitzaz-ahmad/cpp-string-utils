# CMakeList.txt : CMake project for cpp_string_utils, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.16)
project ("cpp_string_utils" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.6)
project(cg_first)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(test)
enable_testing()
add_test(NAME UnitTests COMMAND Test)
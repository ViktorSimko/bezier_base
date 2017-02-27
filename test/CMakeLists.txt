add_executable(Test main.cpp MatrixTests.cpp)
include_directories(src/)
target_link_libraries(Test VSGraphLib)
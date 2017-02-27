cmake_minimum_required(VERSION 3.6)
project(cg_first)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp)
add_executable(cg_first ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(cg_first ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
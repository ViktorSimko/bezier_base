set(SOURCE_FILES main.cpp)
add_executable(cg_first ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_library(VSGraphLib Matrix.cpp)

target_link_libraries(cg_first ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} VSGraphLib)
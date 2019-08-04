cmake_minimum_required(VERSION 3.8)
project(RG145_sort)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/callbackfunc.cpp
    )

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(sort ${SOURCE_FILES})

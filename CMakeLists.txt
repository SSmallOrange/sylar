cmake_minimum_required(VERSION 3.22)
project(sylar)

set(LIB_SRC
        sylar/log.cpp
        tests/test.cpp sylar/util.h sylar/util.cpp sylar/singleton.h)
add_library(sylar SHARED ${LIB_SRC})
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")
set(CMAKE_CXX_STANDARD 17)

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
target_link_libraries(test sylar)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_executable(workspace main.cpp sylar/log.h sylar/log.cpp)

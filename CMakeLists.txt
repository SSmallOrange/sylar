cmake_minimum_required(VERSION 3.22)
project(sylar)

include_directories(.)
include_directories(../yaml/yaml-cpp/include/yaml-cpp)

link_directories(lib)
#
#link_directories(../yaml/yaml-cpp/include/yaml-cpp/)

set(LIB_SRC
        sylar/log.cpp
        sylar/util.cpp
        sylar/config.cpp)
add_library(sylar SHARED ${LIB_SRC})
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")
set(CMAKE_CXX_STANDARD 17)

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
target_link_libraries(test sylar yaml-cpp)

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar)
target_link_libraries(test_config sylar yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_executable(workspace main.cpp)

#add_executable(log ${sylar/log.h})
#add_executable(singleton sylar/singleton.h)
cmake_minimum_required(VERSION 3.22)
project(sylar)
#####
include (cmake/utils.cmake)

include_directories(.)
include_directories(../yaml/yaml-cpp/include/yaml-cpp)

link_directories(lib)

find_library(PTHREAD pthread)

#
#link_directories(../yaml/yaml-cpp/include/yaml-cpp/)

set(LIB_SRC
        sylar/log.cpp
        sylar/util.cpp
        sylar/config.cpp
        sylar/thread.cpp)

add_library(sylar SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(sylar)  # 重定义__FILE__为相对路径（之前是绝对路径）
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

set(LIB_LIB
        sylar
        pthread
        yaml-cpp)

set(CMAKE_CXX_FLAGS "-Wbuiltin-macro-redefined -Werror -Wno-unused-function -Wno-builtin-macro-redefined")
set(CMAKE_CXX_STANDARD 17)

add_executable(test tests/test.cpp)
add_dependencies(test sylar)
force_redefine_file_macro_for_sources(test)
target_link_libraries(test sylar yaml-cpp)

add_executable(test_config tests/test_config.cpp)
add_dependencies(test_config sylar)
force_redefine_file_macro_for_sources(test_config)
target_link_libraries(test_config sylar yaml-cpp)

add_executable(test_thread tests/test_thread.cpp)
add_dependencies(test_thread sylar)
force_redefine_file_macro_for_sources(test_thread)
target_link_libraries(test_thread ${LIB_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


add_executable(workspace main.cpp)

#add_executable(log ${sylar/log.h})
#add_executable(singleton sylar/singleton.h)
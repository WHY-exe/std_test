cmake_minimum_required(VERSION 3.11...3.20)
set(current_bin_name common)
# 设置c++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# setting up include dir
set(INCLUDE_BASE ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_BASE})
include_directories(${INCLUDE_BASE}/common)
# 设置Debug编译选项
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -Werror -g -ggdb")
# 设置Release编译选项
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# setting up linking dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
link_directories(${LIBRARY_OUTPUT_PATH})
# setting up compile options
add_definitions(-DSPDLOG_COMPILED_LIB)
# message(${PROJECT_BINARY_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src common_lib_src)
add_library(${current_bin_name} SHARED ${common_lib_src})
target_link_libraries(${current_bin_name} 
    PUBLIC
    spdlog
)
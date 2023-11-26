cmake_minimum_required(VERSION 3.16...3.20)
# C++标准
set(current_bin_name test_exec)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置Debug编译选项
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -Werror -g -ggdb")
# 设置Release编译选项
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# 设置二进制输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
# setting up include dir
set(INCLUDE_BASE ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_BASE})
include_directories(${INCLUDE_BASE}/common)
# set exec file path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
# 不使用头文件编译spdlog
add_definitions(-DSPDLOG_COMPILED_LIB)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src main)
add_executable(${current_bin_name} ${main})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
# add library linking dir
target_link_directories(${current_bin_name} 
    PRIVATE
    ${LIBRARY_OUTPUT_PATH}
)

target_link_libraries(${current_bin_name} 
    PUBLIC
    common 
    spdlog
)


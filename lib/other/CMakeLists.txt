cmake_minimum_required(VERSION 3.11...3.20)
# 当前二进制对象
set(current_bin_name other)
# 设置c++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置Debug编译选项
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -Werror -g -ggdb")
# 设置Release编译选项
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# setting up compile options
add_definitions(-DSPDLOG_COMPILED_LIB)
# 二进制文件输入
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src common_lib_src)
add_library(${current_bin_name} SHARED ${common_lib_src})
# setting up include dir
set(INCLUDE_BASE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${current_bin_name}
    PRIVATE
    ${INCLUDE_BASE}
    ${INCLUDE_BASE}/common
    ${INCLUDE_BASE}/other
)
# 设置链接路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
target_link_directories(${current_bin_name} 
    PRIVATE
    ${LIBRARY_OUTPUT_PATH}
)
# 链接的库
target_link_libraries(${current_bin_name} 
    PUBLIC
    spdlog
)
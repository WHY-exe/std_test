cmake_minimum_required(VERSION 3.16...3.20)
set(current_bin_name test_exec)
# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置Debug编译选项
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -Werror -g -ggdb")
# 设置Release编译选项
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# 设置二进制输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
# 不使用头文件编译spdlog
add_definitions(-DSPDLOG_COMPILED_LIB)
# 二进制文件输入
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src main)
add_executable(${current_bin_name} ${main})
# setting up include dir
set(INCLUDE_BASE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${current_bin_name}
    PRIVATE
    ${INCLUDE_BASE}
    ${INCLUDE_BASE}/common
    ${INCLUDE_BASE}/other
)
# add library linking dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
target_link_directories(${current_bin_name} 
    PRIVATE
    ${LIBRARY_OUTPUT_PATH}
)
# 链接的库
target_link_libraries(${current_bin_name} 
    PRIVATE
    other
    common 
    spdlog
)


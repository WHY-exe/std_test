cmake_minimum_required(VERSION 3.16...3.20)
set(current_bin_name test)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# coverage option
option (ENABLE_COVERAGE "Use gcov" ON)
message(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
# 设置Debug编译选项
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -Werror -g -ggdb")
# 设置Release编译选项
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# 设置二进制输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/)
# setting up include dir
set(INCLUDE_BASE ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_BASE})
include_directories(${INCLUDE_BASE}/common)
# add library linking dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
link_directories(${LIBRARY_OUTPUT_PATH})
# set exec file path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src tmain)

add_definitions(-DSPDLOG_COMPILED_LIB)
enable_testing()

add_executable(${current_bin_name} 
    ${tmain}
)

target_link_libraries(${current_bin_name} 
    PUBLIC
    common
    PRIVATE 
    gtest 
    gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET ${current_bin_name} )
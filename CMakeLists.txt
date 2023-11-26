cmake_minimum_required(VERSION 3.11...3.20)
# enter your project name here
project(project_name)
add_subdirectory(lib)
add_subdirectory(test_exec)
option(EnableTest "Enable test" ON)
if(${EnableTest})
    add_subdirectory(test)
endif()
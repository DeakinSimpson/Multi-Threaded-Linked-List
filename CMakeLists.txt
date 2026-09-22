cmake_minimum_required(VERSION 4.3)
project(Multi_Threaded_Linked_List)

set(CMAKE_CXX_STANDARD 14)

add_executable(Multi_Threaded_Linked_List
        src/main.cpp)

target_include_directories(Multi_Threaded_Linked_List PRIVATE include)
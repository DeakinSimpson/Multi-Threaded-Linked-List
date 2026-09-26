cmake_minimum_required(VERSION 4.2.3)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "")

project(Multi_Threaded_Linked_List)

set(CMAKE_CXX_STANDARD 26)

add_executable(Multi_Threaded_Linked_List
        src/main.cpp)

target_include_directories(Multi_Threaded_Linked_List PRIVATE include)
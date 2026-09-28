cmake_minimum_required(VERSION 4.2.3)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "")

project(Multi_Threaded_Linked_List)

set(CMAKE_CXX_STANDARD 26)

add_executable(Multi_Threaded_Linked_List
        src/main.cpp)

target_include_directories(Multi_Threaded_Linked_List PRIVATE include)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)

FetchContent_MakeAvailable(googletest)

# --- add google testing ---
add_executable(tslinkedlist_tests
        tests/ThreadSafeLinkedListTest.cpp
)

target_include_directories(tslinkedlist_tests PRIVATE include)
target_link_libraries(tslinkedlist_tests gtest_main)

# integrates gtest with ctest
enable_testing()
include(GoogleTest)
gtest_discover_tests(tslinkedlist_tests)

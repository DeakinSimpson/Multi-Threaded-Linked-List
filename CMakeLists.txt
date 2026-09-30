cmake_minimum_required(VERSION 4.2.3)

project(Multi_Threaded_Linked_List)

set(CMAKE_CXX_STANDARD 26)

add_executable(Multi_Threaded_Linked_List
        src/main.cpp)

target_include_directories(Multi_Threaded_Linked_List PRIVATE include)

include(FetchContent)

FetchContent_Declare(
        googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.1
)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip)

# ignore googles own testing
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
# ignore WERROR for google as it was causing compile errors on my windows device
set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)


FetchContent_MakeAvailable(googlebenchmark googletest)

add_executable(bench
        benchmarks/benchmark.cpp
)

target_include_directories(bench PRIVATE include)
target_link_libraries(bench PRIVATE benchmark::benchmark)

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

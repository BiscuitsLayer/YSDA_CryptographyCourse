cmake_minimum_required(VERSION 3.10)
project(KuznechikCypher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN_TARGET "MainTarget")
file(GLOB MAIN_TARGET_SRC "main.cpp" "src/*")
add_executable(${MAIN_TARGET} ${MAIN_TARGET_SRC})
target_include_directories(${MAIN_TARGET} PUBLIC "include/")

# Extra targets for profiling with GPROF tool
if(UNIX)
    # UNIX speed flag
    set(CMAKE_CXX_FLAGS "-Ofast")

    # Profiler
    set(PROFILER_TARGET "ProfilerTarget")
    add_executable(${PROFILER_TARGET} ${MAIN_TARGET_SRC} ${MAIN_TARGET_SRC})
    target_compile_options(${PROFILER_TARGET} PUBLIC "-pg")
    target_include_directories(${PROFILER_TARGET} PUBLIC "include/")
else(UNIX)
    # Windows speed flag
    set(CMAKE_CXX_FLAGS "/Ox")
endif(UNIX)

# Google Test
include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable tests
enable_testing()

set(TEST_TARGET "TestTarget")
file(GLOB TEST_TARGET_SRC "test.cpp" "src/*")
add_executable(${TEST_TARGET} ${TEST_TARGET_SRC})
target_include_directories(${TEST_TARGET} PUBLIC "include/")
target_link_libraries(${TEST_TARGET} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})
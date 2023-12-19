cmake_minimum_required(VERSION 3.10)
project(KuznechikCypher)

# Compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization levels
add_definitions(-DOPTIMIZATION_LEVEL_1)

# Main target
set(MAIN_TARGET "MainTarget")
file(GLOB MAIN_TARGET_SRC "main.cpp" "src/*")
add_executable(${MAIN_TARGET} ${MAIN_TARGET_SRC})
target_include_directories(${MAIN_TARGET} PUBLIC "include/")

# Enable tests
enable_testing()

# Test target
set(TEST_TARGET "TestTarget")
file(GLOB TEST_TARGET_SRC "test.cpp" "src/*")
add_executable(${TEST_TARGET} ${TEST_TARGET_SRC})
target_include_directories(${TEST_TARGET} PUBLIC "include/")
target_link_libraries(${TEST_TARGET} GTest::gtest_main)

# Discover tests
include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})

if(UNIX)
    # UNIX speed flag
    target_compile_options(${MAIN_TARGET} PUBLIC "-Ofast")
    target_compile_options(${TEST_TARGET} PUBLIC "-Ofast")
else(UNIX)
    # Windows speed flag
    # target_compile_options(${MAIN_TARGET} PUBLIC "/Ox")
    # target_compile_options(${TEST_TARGET} PUBLIC "/Ox")
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

# Profiler target
# To execute profiler run the following commands:
#   ./ProfilerTarget
#   gprof ProfilerTarget > profiler_results.txt
#   cat profiler_results.txt
# At the top you will see the timing for each function
if(UNIX)
    set(PROFILER_TARGET "ProfilerTarget")
    add_executable(${PROFILER_TARGET} ${TEST_TARGET_SRC})
    target_include_directories(${PROFILER_TARGET} PUBLIC "include/")
    target_link_libraries(${PROFILER_TARGET} GTest::gtest_main)

    # Add flag to link GPROF tool
    target_link_options(${PROFILER_TARGET} PUBLIC "-pg")
endif(UNIX)
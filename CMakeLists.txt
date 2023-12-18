cmake_minimum_required(VERSION 3.10)
project(KuznechikCypher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

set(MAIN_TARGET "MainTarget")
file(GLOB MAIN_TARGET_SRC "main.cpp" "src/*")
add_executable(${MAIN_TARGET} ${MAIN_TARGET_SRC})
target_include_directories(${MAIN_TARGET} PUBLIC "include/")

# Extra targets for address/memory checks on UNIX
if(UNIX)
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_CXX_FLAGS    "-Wall -g -std=c++17")

    # Address sanitizer
    add_executable(AddressSanitizerTarget ${MAIN_TARGET_SRC})
    target_compile_options(AddressSanitizerTarget PRIVATE -fsanitize=address)
    target_link_options(AddressSanitizerTarget PRIVATE -fsanitize=address)

    # Memory sanitizer
    add_executable(MemorySanitizerTarget ${MAIN_TARGET_SRC})
    target_compile_options(MemorySanitizerTarget PRIVATE -fsanitize=memory)
    target_link_options(MemorySanitizerTarget PRIVATE -fsanitize=memory)

    # UB sanitizer
    add_executable(UBSanitizerTarget ${MAIN_TARGET_SRC})
    target_compile_options(UBSanitizerTarget PRIVATE -fsanitize=undefined)
    target_link_options(UBSanitizerTarget PRIVATE -fsanitize=undefined)
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
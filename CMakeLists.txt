cmake_minimum_required(VERSION 3.10)
project(cppLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Global include directory
include_directories(${PROJECT_SOURCE_DIR}/include)
# Set executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -------------------------- ONLY Build Main Program (main.cpp ONLY) --------------------------
# ✅ Critical Fix: Compile main.cpp ALONE, no test files included
if(EXISTS ${PROJECT_SOURCE_DIR}/main.cpp)
    add_executable(cppLearning_main main.cpp)
    set_target_properties(cppLearning_main PROPERTIES OUTPUT_NAME "cppLearning_main")
endif()

# -------------------------- Auto CTest for Test Directory (FULLY SEPARATED) --------------------------
enable_testing()
file(GLOB_RECURSE TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.cpp)

if(TEST_SOURCES)
    foreach(TEST_SRC ${TEST_SOURCES})
        get_filename_component(TEST_TARGET ${TEST_SRC} NAME_WE)
        # ✅ Each test file is compiled as an INDEPENDENT executable (no link to main)
        add_executable(${TEST_TARGET} ${TEST_SRC})
        # Register to CTest
        add_test(
            NAME ${TEST_TARGET}
            COMMAND ${TEST_TARGET}
            WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
        # Test properties
        set_tests_properties(${TEST_TARGET} PROPERTIES
            TIMEOUT 10
            FAIL_REGULAR_EXPRESSION "Assertion failed;ERROR;Failed"
            PASS_REGULAR_EXPRESSION "OK;Pass;SUCCESS"
        )
    endforeach()
else()
    message(WARNING "No test files found in [test/] directory! Add *.cpp.")
endif()
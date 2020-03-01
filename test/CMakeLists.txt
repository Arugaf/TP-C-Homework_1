cmake_minimum_required(VERSION 3.9)

set(test_name matrix_test)

set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")

add_executable(${test_name} ${tests})

target_link_libraries(${test_name} ${project_name}_lib gtest_main gtest)

add_test(NAME ${test_name} COMMAND ${test_name})
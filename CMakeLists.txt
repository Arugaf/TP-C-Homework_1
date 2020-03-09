cmake_minimum_required(VERSION 3.9)

set(project_name TP_C_Homework_1)
project(${project_name})

set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_C_STANDARD 11)

set(includes ${PROJECT_SOURCE_DIR}/include)
include_directories(${includes})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(${project_name} ${sources})

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)

add_library(${project_name}_lib STATIC ${PROJECT_SOURCE_DIR}/src/matrix.c)

if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()
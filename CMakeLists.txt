cmake_minimum_required(VERSION 3.9)

set(project_name TP_C_Homework_1)
project(${project_name})

set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_C_STANDARD 11)

if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()

set(includes ${PROJECT_SOURCE_DIR}/include)
include_directories(${includes})

add_executable(${project_name} src/main.c)

enable_testing()
add_subdirectory(googletest)
add_subdirectory(test)

add_library(${project_name}_lib STATIC ${PROJECT_SOURCE_DIR}/src/matrix.c)

target_link_libraries(${project_name} ${project_name}_lib)
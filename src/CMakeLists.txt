cmake_minimum_required(VERSION 3.10)

project(compreC C)

add_executable(compreC main.c interface.c zipUtils.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(compreC ncursesw zip) 
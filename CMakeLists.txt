cmake_minimum_required(VERSION 3.10)
project(VirusTracker)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")

add_library(testdaten SHARED testdaten.c)
add_executable(test main.c)
target_link_libraries(test testdaten)

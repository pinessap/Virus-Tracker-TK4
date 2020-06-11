cmake_minimum_required(VERSION 3.10)
project(VirusTracker)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pedantic -Wfatal-errors -pedantic-errors")

add_library(testdaten SHARED testdaten.c)
add_library(dijkstra SHARED dijkstra.c)
add_library(graphviz SHARED graphviz.c)

add_executable(virus_tracker main.c)
target_link_libraries(virus_tracker testdaten dijkstra graphviz)
target_link_libraries(graphviz testdaten)
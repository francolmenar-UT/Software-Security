cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SortedTree LANGUAGES C)

enable_testing()

add_subdirectory(main)
add_subdirectory(tree)

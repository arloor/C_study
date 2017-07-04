cmake_minimum_required(VERSION 3.7)
project(C_study)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c memory_alloc.c memory_alloc.h static_var_use.c static_var_use.h)
add_executable(C_study ${SOURCE_FILES})
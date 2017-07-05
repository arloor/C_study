cmake_minimum_required(VERSION 3.7)
project(C_study)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c memory_alloc.c header/memory_alloc.h static_var_use.c header/static_var_use.h fget_read_line_from_stream.c header/fget_read_line_from_stream.h pointer.c header/pointer.h non_buffer_io.c header/non_buffer_io.h)
add_executable(C_study ${SOURCE_FILES})
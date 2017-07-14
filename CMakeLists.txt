cmake_minimum_required(VERSION 3.7)
project(C_study)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c memory_alloc.c header/memory_alloc.h static_var_use.c header/static_var_use.h fget_read_line_from_stream.c header/fget_read_line_from_stream.h pointer.c header/pointer.h non_buffer_io.c header/non_buffer_io.h std_io.c header/std_io.h thread_prac1.c header/thread_prac1.h thread_prac2_rwlock.c header/thread_prac2_rwlock.h thread_prac3_cond.c header/thread_prac3_cond.h
        header/ds_seqList_array.h ds_seqList_array.c)
add_executable(C_study ${SOURCE_FILES})
#下面是针对线程相关的配置
find_package(Threads REQUIRED)
target_link_libraries(C_study Threads::Threads)
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(test_lib VERSION 1.0.0 LANGUAGES C)
add_library(test_lib SHARED test_lib.c test_lib.def)
add_executable(test_lib_test test_lib.c)

set_target_properties(test_lib PROPERTIES
    PUBLIC_HEADER test_lib.h
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME "test_lib"
)
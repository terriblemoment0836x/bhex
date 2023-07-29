cmake_minimum_required(VERSION 3.20)
project(hex_dumper)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-cc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

add_executable(hex_dump src/main.c)

cmake_minimum_required(VERSION 3.20)
project(hex_dumper)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-cc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(hex_dump src/main.c src/utils.c)

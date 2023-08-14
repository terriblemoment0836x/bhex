cmake_minimum_required(VERSION 3.20)
project(hex_dumper)

include(CTest)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-cc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

set(CMAKE_C_FLAGS "-g -Wall -Wextra")

add_executable(bhex src/main.c src/utils.c src/dump.c src/search.c)

add_executable(test_search test/test_search.c src/search.c)

add_test(test_search::buffer_search_preproccess ../bin/test_search buffer_search_preproccess)

add_test(test_search::buffer_search ../bin/test_search buffer_search)
add_test(test_search::buffer_search_hdex ../bin/test_search buffer_search_hex)

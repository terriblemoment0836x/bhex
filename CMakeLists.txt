cmake_minimum_required(VERSION 3.20)
project(bhex)

include(CTest)
include(CheckIncludeFiles)

check_include_files( windows.h HAVE_WINDOWS_H )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h)
# set(CMAKE_C_COMPILER x86_64-w64-mingw32-cc)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)

set(CMAKE_C_FLAGS "-g -Wall -Wextra")

add_executable(bhex src/main.c src/dump.c src/search.c src/utils.c)
target_link_libraries(bhex m)

add_executable(test_search test/test_search.c src/search.c)
add_test(test_search::buffer_search_preproccess ../bin/test_search buffer_search_preproccess)
add_test(test_search::buffer_search ../bin/test_search buffer_search)
add_test(test_search::buffer_search_hdex ../bin/test_search buffer_search_hex)

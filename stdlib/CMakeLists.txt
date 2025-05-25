cmake_minimum_required(VERSION 3.30)
project(lgslib C)

set(CMAKE_C_STANDARD 11)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(lgslib STATIC
    lib/HashMap.c
    lib/Array.c
    lib/VTable.c
    lib/Str.c
    lib/Runtime.c
)

add_executable(bla test.c)
target_link_libraries(bla lgslib)

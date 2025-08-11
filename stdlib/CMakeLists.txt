project(lgslib C)

add_library(lgslib STATIC
    lib/HashMap.c
    lib/Array.c
    lib/Str.c
    lib/Runtime.c
    lib/System.c
    include/System.h
)

target_include_directories(lgslib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../stdlib/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/configs
)
project(lgslib C)

add_library(lgslib STATIC
    lib/HashMap.c
    lib/Array.c
    lib/Str.c
    lib/System.c
)

target_include_directories(lgslib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/configs
)
add_library(lgslib STATIC
    lib/HashMap.c
    lib/Array.c
    lib/Str.c
    lib/Runtime.c
    lib/Print.c
)

target_include_directories(lgslib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../stdlib/include
)
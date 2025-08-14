project(lgs_runtime C CXX)

add_library(lgs_runtime
    lib/Lgs_hashmap.c
    lib/Lgs_array.c
    lib/Lgs_helpers.c
    lib/Lgs_system.cpp
    lib/Lgs_defer.c
    lib/Lgs_stack.c
)

target_include_directories(lgs_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/configs
)

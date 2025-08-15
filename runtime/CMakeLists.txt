project(lgs_runtime C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(lgs_runtime
    lib/Lgs_hashmap.c
    lib/Lgs_array.c
    lib/Lgs_helpers.cpp
    lib/Lgs_system.cpp
    lib/Lgs_defer.c
    include/Lgs_Stack.h
    lib/Lgs_runtime.c
    include/Lgs_runtime.h
)

target_include_directories(lgs_runtime PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/configs
)

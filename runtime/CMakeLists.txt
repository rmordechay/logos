project(lgs_runtime C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(Boost CONFIG REQUIRED context coroutine)

add_library(lgs_runtime SHARED
    lib/Lgs_hashmap.c
    lib/Lgs_array.cpp
    lib/Lgs_helpers.cpp
    lib/Lgs_system.cpp
    lib/Lgs_defer.c
    lib/Lgs_runtime.cpp
    lib/Lgs_scheduler.cpp
)

target_link_libraries(lgs_runtime PUBLIC
    Boost::context
    Boost::coroutine
)

target_include_directories(lgs_runtime PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/configs
)

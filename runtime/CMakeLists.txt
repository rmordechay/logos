project(lgs_runtime CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost CONFIG REQUIRED context coroutine)

add_library(lgs_runtime SHARED
    lib/Lgs_hashmap.cpp
    lib/Lgs_array.cpp
    lib/Lgs_helpers.cpp
    lib/Lgs_system.cpp
    lib/Lgs_defer.cpp
    lib/Lgs_runtime.cpp
    lib/Lgs_scheduler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/utils/LgsUtils.cpp
)

target_link_libraries(lgs_runtime PUBLIC
    Boost::context
    Boost::coroutine
    LLVM
    clang-cpp
)

target_precompile_headers(lgs_runtime PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/pch.h)
target_include_directories(lgs_runtime PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../runtime/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/symbols
)

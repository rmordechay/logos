cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 10)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")

include(ProcessorCount)
ProcessorCount(CPU_COUNT)
set(CMAKE_BUILD_PARALLEL_LEVEL ${CPU_COUNT})

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS include/*.h)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp)
add_library(lib ${HEADER_FILES} ${SOURCE_FILES})


target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/analysis
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen
    ${CMAKE_CURRENT_SOURCE_DIR}/include/data
    ${CMAKE_CURRENT_SOURCE_DIR}/include/files
    ${CMAKE_CURRENT_SOURCE_DIR}/include/logos
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libLLVM.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldCommon.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldMachO.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libantlr.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(ZLIB REQUIRED)
    target_link_libraries(lib PRIVATE
        ZLIB::ZLIB
        zstd
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libLLVM.so
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/liblldELF.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/liblldCommon.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libantlr.a
    )
endif()

add_executable(lgs main.cpp)
target_link_libraries(lgs PRIVATE lib)
# add_subdirectory(tests)

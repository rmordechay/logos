cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/antlr4-runtime")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/include/libantlr4-runtime.a")

file(GLOB GENERATED_SRC "gen/*.cpp" "gen/*.h")

add_executable(logos main.cpp ${GENERATED_SRC})

target_include_directories(logos PRIVATE
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gen
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(logos PRIVATE ${ANTLR_LIB})

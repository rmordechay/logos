cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE LOGOS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.h
)
file(GLOB_RECURSE LOGOS_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.cpp
)

add_executable(logos main.cpp ${LOGOS_SRC} ${LOGOS_HEADERS}
    src/symbols/stmts/LogosStmtBlock.cpp
    include/symbols/stmts/LogosStmtBlock.h)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime")
target_include_directories(logos PRIVATE
    src/parser
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/application"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/codegen"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sema"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/symbols"
)

set(LLVM_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libLLVM.dylib")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a")

target_link_libraries(logos PRIVATE ${ANTLR_LIB} ${LLVM_LIB})
add_executable(logos_tests tests/ParserTest.cpp)

#set(GTEST_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest.1.15.2.dylib")
#set(GTEST_LIB_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest_main.1.15.2.dylib")
#target_include_directories(logos_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/include)
#target_link_libraries(logos_tests PRIVATE ${GTEST_LIB} ${GTEST_LIB_MAIN})
#enable_testing()
#add_test(NAME LogosTests COMMAND logos_tests)



cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/antlr4-runtime")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/include/libantlr4-runtime.a")

file(GLOB GENERATED_SRC "logos/parser/*.cpp" "logos/parser/*.h")

find_package(LLVM REQUIRED CONFIG)

add_executable(logos
    main.cpp
    ${GENERATED_SRC}
    logos/project/Project.cpp
    logos/project/Project.h
    logos/project/LogosFile.cpp
    logos/project/LogosFile.h
    logos/sema/SemAnalyser.cpp
    logos/sema/SemAnalyser.h
)

target_include_directories(logos PRIVATE
    logos/parser
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
)
llvm_map_components_to_libnames(LLVM_LIBS core)
target_link_libraries(logos PRIVATE ${ANTLR_LIB} ${LLVM_LIBS})

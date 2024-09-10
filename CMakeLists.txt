cmake_minimum_required(VERSION 3.28)
project(logos C)

set(CMAKE_C_STANDARD 11)
set(GEN_DIR_BUILD ${CMAKE_BINARY_DIR}/gen)
set(GEN_DIR_SOURCE ${CMAKE_SOURCE_DIR}/gen)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(CURL REQUIRED)
find_package(LLVM REQUIRED CONFIG)

file(MAKE_DIRECTORY ${GEN_DIR_SOURCE})
BISON_TARGET(
    Parser grammar/parser.y ${GEN_DIR_SOURCE}/parser.c
    DEFINES_FILE ${GEN_DIR_SOURCE}/parser.h
    COMPILE_FLAGS -v
)
FLEX_TARGET(Lexer grammar/lexer.l ${GEN_DIR_SOURCE}/lexer.c)
add_flex_bison_dependency(Lexer Parser)

set(
    SOURCES
    include/cJSON.c
    src/utils/utils.h
    gen/parser.c
    gen/lexer.c
    src/project/project.c
    src/project/project.h
    src/project/application.c
    src/ast/tree.c
    main.c
    src/utils/json_ast.c
    src/analyser/analysis.c
    src/analyser/analysis.h
    src/utils/hashmap.c
    src/utils/hashmap.h
    src/analyser/errors.h
    src/lang/object.c
    src/codegen/code_generator.c
    src/codegen/code_generator.h
    test.c
)

add_executable(logos ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS} ${SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${GEN_DIR_SOURCE}
    ${GEN_DIR_BUILD}
    ${LLVM_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})

set_target_properties(logos PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
llvm_map_components_to_libnames(llvm_libs core orcjit native)

target_link_libraries(logos CURL::libcurl ${llvm_libs} "-lc++" "-lc++abi")

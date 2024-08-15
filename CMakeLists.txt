cmake_minimum_required(VERSION 3.28)
project(mylang C)

set(CMAKE_C_STANDARD 11)
set(GEN_DIR_BUILD ${CMAKE_BINARY_DIR}/gen)
set(GEN_DIR_SOURCE ${CMAKE_SOURCE_DIR}/gen)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(CURL REQUIRED)




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
    src/compiler/analyser.c
    src/ast/ast.c
    src/utils/utils.c
    ${GEN_DIR_SOURCE}/parser.c
    ${GEN_DIR_SOURCE}/lexer.c
    main.c
)

add_executable(mylang ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS} ${SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

set_target_properties(mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_link_libraries(mylang CURL::libcurl)

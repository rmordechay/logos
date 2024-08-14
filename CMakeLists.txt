cmake_minimum_required(VERSION 3.28)
project(mylang C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)
include_directories(include)

add_executable(
    mylang
    main.c
    gen/lexer.c
    gen/parser.c
    gen/parser.h
    ast/ast.c
    ast/ast.h
    compiler/compiler.c
    compiler/compiler.h
    utils/utils.c
    utils/utils.h
    include/cJSON.c
)

set_target_properties(mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(mylang CURL::libcurl)

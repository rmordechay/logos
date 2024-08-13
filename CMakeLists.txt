cmake_minimum_required(VERSION 3.28)
project(mylang C)

set(CMAKE_C_STANDARD 11)

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
)

set_target_properties(mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

cmake_minimum_required(VERSION 3.28)
project(Mylang C)

set(CMAKE_C_STANDARD 11)

add_executable(
    Mylang
    main.c
    gen/lexer.c
    gen/parser.c
    gen/parser.h
    ast/ast.c
    ast/ast.h
)

set_target_properties(Mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

cmake_minimum_required(VERSION 3.28)
project(Mylang C)

set(CMAKE_C_STANDARD 11)

add_executable(Mylang gen/lex.yy.c gen/parser.c main.c)

set_target_properties(Mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

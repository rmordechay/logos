cmake_minimum_required(VERSION 3.28)
project(mylang C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES
    include/cJSON.c
    gen/parser.c
    gen/lexer.c
    compiler/analyser.c
    ast/ast.c
    main.c
)

add_executable(mylang ${SOURCES})

set_target_properties(mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(mylang CURL::libcurl)

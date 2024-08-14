cmake_minimum_required(VERSION 3.28)
project(mylang C)

set(CMAKE_C_STANDARD 11)
set(GEN_DIR gen)

find_package(CURL REQUIRED)

set(
    SOURCES
    include/cJSON.c
    ${GEN_DIR}/parser.c
    ${GEN_DIR}/lexer.c
    compiler/analyser.c
    ast/ast.c
    main.c
    utils/utils.c
)

add_executable(mylang ${SOURCES})

target_include_directories(mylang PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}
)

set_target_properties(mylang PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

target_link_libraries(mylang CURL::libcurl)

enable_testing()

add_executable(lgs_tests
    main.cpp
    parser/ParserErrorTest.cpp
    codegen/CodegenTest.cpp
    sema/SemaErrorTest.cpp
    parser/ParserTest.cpp
)

set_target_properties(lgs_tests PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

target_include_directories(lgs_tests PRIVATE ${CMAKE_SOURCE_DIR}/tests)
target_link_libraries(lgs_tests PRIVATE lgs_lib)
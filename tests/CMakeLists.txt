enable_testing()

add_executable(lgs_tests
    main.cpp
    parser/ParserErrorTest.cpp
    codegen/CodegenTest.cpp
    sema/SemaErrorTest.cpp
    parser/ParserTest.cpp
)

target_precompile_headers(lgs_tests REUSE_FROM lgs_core)
target_include_directories(lgs_tests PRIVATE /Users/r.mordechay/Desktop/Programming/logos/tests/helpers.h)
target_link_libraries(lgs_tests PRIVATE lgs_core)
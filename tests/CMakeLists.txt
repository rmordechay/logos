enable_testing()

add_executable(lgs_tests
    main.cpp
    parser/ParserErrorTest.cpp
    codegen/CodegenTest.cpp
    sema/SemaErrorTest.cpp
)
target_precompile_headers(lgs_tests REUSE_FROM lgs_core)
target_link_libraries(lgs_tests PRIVATE lgs_core lgs_runtime)
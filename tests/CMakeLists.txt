enable_testing()


add_executable(lgs_tests
    main.cpp
    parser/ParserTest.cpp
    codegen/CodegenTest.cpp
    sema/SemaTest.cpp
)
target_include_directories(lgs_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../external/include/doctest.h
)

target_precompile_headers(lgs_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/pch.h)
target_link_libraries(lgs_tests PRIVATE lib)

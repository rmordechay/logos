enable_testing()

add_executable(lgs_tests
    main.cpp
    parser/ParserErrorTest.cpp
    codegen/CodegenTest.cpp
    sema/SemaErrorTest.cpp
    parser/ParserTest.cpp
    ${LGS_SOURCE}
)

target_include_directories(lgs_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/external
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/symbols
    ${CMAKE_SOURCE_DIR}/runtime/include
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

target_link_libraries(lgs_tests PRIVATE lgs_runtime LLVM clang-cpp)
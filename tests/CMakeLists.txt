find_package(GTest REQUIRED)
enable_testing()

add_executable(lgs_tests
    ${COMPILER_SOURCE}
    main.cpp
    LgsTestUtils.h
    parser/ParserTest.cpp
    sema/ErrorsTest.cpp
    sema/TypeResolverTest.cpp
    codegen/CgMemoryTest.cpp
    codegen/CgIfStmtTest.cpp
    codegen/CgLoopsTest.cpp
    codegen/CgGenericsTest.cpp
    codegen/CgDeferTest.cpp
    codegen/CgObjectTest.cpp
    codegen/CgAssignTest.cpp
    codegen/CgIOPairTest.cpp
    codegen/CgInterfaceTest.cpp
    codegen/exprs/CgBinExprTest.cpp
    codegen/exprs/CgArraysTest.cpp
    codegen/exprs/CgStrTest.cpp
    codegen/exprs/CgVecTest.cpp
    codegen/exprs/CgLambdaTest.cpp
    codegen/exprs/CgFuncCallTest.cpp
    codegen/exprs/CgUnaryExprTest.cpp
    codegen/exprs/CgNullableTest.cpp
)

target_include_directories(lgs_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/compiler/include
    ${CMAKE_SOURCE_DIR}/compiler/include/symbols
    ${CMAKE_SOURCE_DIR}/lib/include
    ${CMAKE_SOURCE_DIR}/shared/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

target_link_libraries(lgs_tests PRIVATE
    lgs_shared
    lgs_lib
    LLVM
    clang-cpp
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
    GTest::gtest
    GTest::gtest_main
)
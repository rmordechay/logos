find_package(GTest REQUIRED)
enable_testing()

add_executable(lgs_tests
    main.cpp
    LgsTestUtils.h
    ${COMPILER_SOURCE}
    parser/ParserTest.cpp
    sema/ErrorsTest.cpp
    sema/TypeResolverTest.cpp
    codegen/CgIfStmtTest.cpp
    codegen/CgLoopsTest.cpp
    codegen/CgBinExprTest.cpp
    codegen/CgArraysTest.cpp
    codegen/CgGenericsTest.cpp
    codegen/CgStrTest.cpp
    codegen/CgVecTest.cpp
    codegen/CgDeferTest.cpp
    codegen/CgLambdaTest.cpp
    codegen/CgObjectTest.cpp
    codegen/CgAssignTest.cpp
    codegen/CgIOPairTest.cpp
    codegen/CgInterfaceTest.cpp
    codegen/CgFuncCallTest.cpp
    codegen/CgUnaryExprTest.cpp
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
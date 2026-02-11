find_package(GTest REQUIRED)
enable_testing()

add_executable(lgs_tests
    main.cpp
    LgsTestUtils.h
    parser/ParserErrorTest.cpp
    parser/ParserTest.cpp
    sema/SemaErrorTest.cpp
    sema/resolver/SArrTest.cpp
    codegen/CgIfStmtTest.cpp
    codegen/CgArithmeticsTest.cpp
    ${COMPILER_SOURCE}
    codegen/CgDArrayTest.cpp
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
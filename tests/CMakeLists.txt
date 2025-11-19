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
    ${CMAKE_SOURCE_DIR}/compiler/include
    ${CMAKE_SOURCE_DIR}/compiler/include/symbols
    ${CMAKE_SOURCE_DIR}/lib/include
    ${CMAKE_SOURCE_DIR}/shared/include
)

target_link_libraries(lgs_tests PRIVATE
    lgs_shared
    lgs_lib
    LLVM
    clang-cpp
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
)

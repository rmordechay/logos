cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime")
set(LLVM_INCLUDE_DIR "/opt/homebrew/opt/llvm/include")
set(LLVM_LIBS "/opt/homebrew/opt/llvm/lib")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a")
set(GTEST_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest.1.15.2.dylib")
set(GTEST_LIB_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest_main.1.15.2.dylib")

file(GLOB GENERATED_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/*.h")
file(GLOB LLVM ${LLVM_LIBS}/libLLVM.dylib ${LLVM_LIBS}/*.a)

add_executable(logos
    main.cpp
    ${GENERATED_SRC}
    include/LogosDefinitions.h
    src/application/Application.cpp
    include/application/Application.h
    src/application/LogosUtils.cpp
    include/application/LogosUtils.h
    src/application/ThreadPool.cpp
    include/application/ThreadPool.h
    src/codegen/CodeGenerator.cpp
    include/codegen/CodeGenerator.h
    include/symbols/LogosStack.h
    src/sema/AntlrConverter.cpp
    include/sema/AntlrConverter.h
    include/sema/LogosErrors.h
    src/sema/SemaAnalyser.cpp
    include/sema/SemaAnalyser.h
    include/symbols/CodeGeneration.h
    src/symbols/exprs/LogosBinaryExpr.cpp
    include/symbols/exprs/LogosBinaryExpr.h
    src/symbols/exprs/LogosConstant.cpp
    include/symbols/exprs/LogosConstant.h
    src/symbols/exprs/LogosConstructor.cpp
    include/symbols/exprs/LogosConstructor.h
    include/symbols/exprs/LogosExpr.h
    src/symbols/exprs/LogosFuncCall.cpp
    include/symbols/exprs/LogosFuncCall.h
    include/symbols/exprs/LogosOperator.h
    include/symbols/exprs/LogosUnaryExpr.h
    src/symbols/exprs/LogosVariable.cpp
    include/symbols/files/LogosFile.h
    src/symbols/files/LogosMainFile.cpp
    include/symbols/files/LogosMainFile.h
    include/symbols/files/LogosMainFile.h
    src/symbols/files/LogosObjectFile.cpp
    include/symbols/files/LogosObjectFile.h
    include/symbols/funcs/LogosFunc.h
    src/symbols/funcs/LogosUserFunc.cpp
    include/symbols/funcs/LogosUserFunc.h
    src/symbols/object/LogosObject.cpp
    include/symbols/object/LogosObject.h
    src/symbols/stmts/LogosIfStmt.cpp
    include/symbols/stmts/LogosIfStmt.h
    src/symbols/stmts/LogosReturnStmt.cpp
    include/symbols/stmts/LogosReturnStmt.h
    include/symbols/stmts/LogosStmt.h
    src/symbols/stmts/LogosVarDec.cpp
    include/symbols/stmts/LogosVarDec.h
    include/symbols/types/LogosBool.h
    include/symbols/types/LogosFloat.h
    include/symbols/types/LogosInt.h
    include/symbols/types/LogosString.h
    include/symbols/types/LogosType.h
    src/symbols/funcs/LogosPrint.cpp
    include/symbols/funcs/LogosPrint.h
    src/symbols/exprs/LogosSelection.cpp
    include/symbols/exprs/LogosSelection.h
    include/symbols/LogosSymbol.h
    src/symbols/object/LogosField.cpp
    include/symbols/object/LogosField.h
)

target_include_directories(logos PRIVATE
    src/parser
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${LLVM_INCLUDE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/application"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/codegen"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/sema"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/symbols"
)

target_link_libraries(logos PRIVATE ${ANTLR_LIB} ${LLVM} ${GTEST_LIB} ${GTEST_LIB_MAIN})

enable_testing()
add_executable(logos_tests tests/ParserTest.cpp)

target_include_directories(logos_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
)

target_link_libraries(logos_tests PRIVATE ${GTEST_LIB} ${GTEST_LIB_MAIN})

add_test(NAME LogosTests COMMAND logos_tests)
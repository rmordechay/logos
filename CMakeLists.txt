cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a")
set(GTEST_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest.1.15.2.dylib")
set(GTEST_LIB_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest_main.1.15.2.dylib")
set(LLVM_LIBS "/opt/homebrew/opt/llvm/lib")
set(LLVM_INCLUDE_DIR "/opt/homebrew/opt/llvm/include")

file(GLOB GENERATED_SRC "${CMAKE_CURRENT_SOURCE_DIR}/logos/parser/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/logos/parser/*.h")

add_executable(logos
    main.cpp
    ${GENERATED_SRC}
    logos/LogosDefinitions.h
    logos/codegen/CodeGenerator.cpp
    logos/codegen/CodeGenerator.h
    logos/symbols/files/LogosFile.h
    logos/project/LogosPackage.cpp
    logos/project/LogosPackage.h
    logos/project/LogosProject.cpp
    logos/project/LogosProject.h
    logos/sema/LogosErrors.h
    logos/sema/AntlrConverter.cpp
    logos/sema/AntlrConverter.h
    logos/symbols/types/LogosType.h
    logos/symbols/types/LogosBool.h
    logos/symbols/types/LogosFloat.h
    logos/symbols/types/LogosInt.h
    logos/symbols/types/LogosString.h
    logos/symbols/exprs/LogosOperator.h
    logos/symbols/exprs/LogosExpr.h
    logos/symbols/exprs/LogosConstantExpr.h
    logos/symbols/exprs/LogosFuncCallExpr.h
    logos/symbols/funcs/LogosFunc.h
    logos/symbols/exprs/LogosUnaryExpr.h
    logos/symbols/exprs/LogosBinaryExpr.h
    logos/codegen/LogosStackFrame.h
    logos/symbols/CodeGeneration.h
    logos/symbols/funcs/LogosPrint.cpp
    logos/symbols/funcs/LogosPrint.h
    logos/symbols/funcs/LogosUserFunc.cpp
    logos/symbols/funcs/LogosUserFunc.h
    logos/symbols/exprs/LogosFuncCallExpr.cpp
    logos/symbols/exprs/LogosConstantExpr.cpp
    logos/symbols/exprs/LogosVariableExpr.cpp
    logos/symbols/exprs/LogosBinaryExpr.cpp
    logos/symbols/exprs/LogosExpr.cpp
    logos/symbols/stmts/LogosVarDec.cpp
    logos/symbols/stmts/LogosVarDec.h
    logos/symbols/stmts/LogosIfStmt.cpp
    logos/symbols/stmts/LogosIfStmt.h
    logos/symbols/stmts/LogosStmt.h
    logos/symbols/files/LogosMainFile.h
    logos/symbols/files/LogosMainFile.h
    logos/symbols/stmts/LogosReturnStmt.cpp
    logos/symbols/stmts/LogosReturnStmt.h
    logos/sema/SemaAnalyser.cpp
    logos/sema/SemaAnalyser.h
    logos/codegen/LogosStack.cpp
    logos/codegen/LogosStack.h
    logos/symbols/exprs/LogosConstructorExpr.cpp
    logos/symbols/exprs/LogosConstructorExpr.h
    logos/symbols/object/LogosObject.cpp
    logos/symbols/object/LogosObject.h
    logos/symbols/types/LogosUserType.h
    logos/symbols/files/LogosObjectFile.h
    logos/project/ThreadPool.cpp
    logos/project/ThreadPool.h
    logos/project/LogosUtils.cpp
    logos/project/LogosUtils.h
    logos/symbols/files/LogosMainFile.cpp
    logos/symbols/files/LogosObjectFile.cpp
)

target_include_directories(logos PRIVATE
    logos
    logos/project
    logos/symbols
    logos/parser
    logos/codegen
    logos/sema
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${LLVM_INCLUDE_DIR}
)

file(GLOB LLVM ${LLVM_LIBS}/libLLVM.dylib ${LLVM_LIBS}/*.a)
target_link_libraries(logos PRIVATE ${ANTLR_LIB} ${LLVM} ${GTEST_LIB} ${GTEST_LIB_MAIN})

enable_testing()
add_executable(logos_tests tests/ParserTest.cpp)

target_include_directories(logos_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
)

target_link_libraries(logos_tests PRIVATE ${GTEST_LIB} ${GTEST_LIB_MAIN})

add_test(NAME LogosTests COMMAND logos_tests)
cmake_minimum_required(VERSION 3.22)
project(logos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/application
    ${CMAKE_CURRENT_SOURCE_DIR}/include/files
    ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sema
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loops
)

add_library(lib STATIC
    src/application/Application.cpp
    src/application/LogosUtils.cpp
    src/application/ThreadPool.cpp
    src/codegen/CodeGenerator.cpp
    src/codegen/LogosLinker.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/sema/AntlrConverter.cpp
    src/sema/SemaAnalyser.cpp
    src/symbols/exprs/LogosBinaryExpr.cpp
    src/symbols/exprs/LogosConstant.cpp
    src/symbols/exprs/LogosFuncCall.cpp
    src/symbols/exprs/LogosInstance.cpp
    src/symbols/exprs/LogosSelection.cpp
    src/symbols/exprs/LogosVariable.cpp
    src/symbols/exprs/LogosArray.cpp
    src/symbols/exprs/LogosArrayIndex.cpp
    src/symbols/funcs/LogosPrint.cpp
    src/symbols/funcs/LogosUserFunc.cpp
    src/symbols/funcs/LogosMethodImpl.cpp
    src/symbols/object/LogosField.cpp
    src/symbols/object/LogosObject.cpp
    src/symbols/stmts/LogosFieldDef.cpp
    src/symbols/stmts/LogosIf.cpp
    src/symbols/stmts/LogosReturn.cpp
    src/symbols/stmts/LogosStmtBlock.cpp
    src/symbols/stmts/LogosVarDec.cpp
    src/symbols/loops/LogosRangeLoop.cpp
    src/symbols/loops/LogosForeachLoop.cpp
    src/symbols/LogosSymbol.cpp
    src/application/CommandLine.cpp
    include/application/CommandLine.h
)

add_executable(logos main.cpp src/LogosStack.cpp)

target_link_libraries(logos PRIVATE lib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libLLVM.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/liblldCommon.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/liblldMachO.dylib
)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols/exprs
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loops
)

add_library(lib STATIC
    include/LogosError.h
    src/application/Application.cpp
    include/application/Application.h
    src/application/ThreadPool.cpp
    include/application/ThreadPool.h
    src/codegen/CodeGenerator.cpp
    include/codegen/CodeGenerator.h
    src/codegen/LogosLinker.cpp
    include/codegen/LogosLinker.h
    src/parser/LogosLexer.cpp
    include/parser/LogosLexer.h
    src/parser/LogosParser.cpp
    include/parser/LogosParser.h
    src/sema/AntlrConverter.cpp
    include/sema/AntlrConverter.h
    src/sema/SemaAnalyser.cpp
    include/sema/SemaAnalyser.h
    src/symbols/exprs/binary/LogosBinaryExpr.cpp
    include/symbols/exprs/binary/LogosBinaryExpr.h
    src/symbols/exprs/unary/constants/LogosConstant.cpp
    include/symbols/exprs/unary/constants/LogosConstant.h
    src/symbols/exprs/unary/LogosFuncCall.cpp
    include/symbols/exprs/unary/LogosFuncCall.h
    src/symbols/exprs/unary/LogosInstance.cpp
    include/symbols/exprs/unary/LogosInstance.h
    src/symbols/exprs/unary/LogosSelection.cpp
    include/symbols/exprs/unary/LogosSelection.h
    src/symbols/exprs/unary/LogosVariable.cpp
    include/symbols/exprs/unary/LogosVariable.h
    src/symbols/exprs/unary/LogosArray.cpp
    include/symbols/exprs/unary/LogosArray.h
    src/symbols/exprs/unary/LogosArrayIndex.cpp
    include/symbols/exprs/unary/LogosArrayIndex.h
    src/symbols/funcs/LogosPrint.cpp
    include/symbols/funcs/LogosPrint.h
    src/symbols/funcs/LogosFuncImpl.cpp
    include/symbols/funcs/LogosFuncImpl.h
    src/symbols/funcs/LogosMethodImpl.cpp
    include/symbols/funcs/LogosMethodImpl.h
    src/symbols/object/LogosField.cpp
    include/symbols/object/LogosField.h
    src/symbols/object/LogosObject.cpp
    include/symbols/object/LogosObject.h
    src/symbols/stmts/LogosAssignment.cpp
    include/symbols/stmts/LogosAssignment.h
    src/symbols/stmts/LogosIf.cpp
    include/symbols/stmts/LogosIf.h
    src/symbols/stmts/LogosReturn.cpp
    include/symbols/stmts/LogosReturn.h
    src/symbols/stmts/LogosStmtBlock.cpp
    include/symbols/stmts/LogosStmtBlock.h
    src/symbols/stmts/LogosVarDec.cpp
    include/symbols/stmts/LogosVarDec.h
    src/symbols/loops/LogosRangeLoop.cpp
    include/symbols/loops/LogosRangeLoop.h
    src/symbols/loops/LogosForeachLoop.cpp
    include/symbols/loops/LogosForeachLoop.h
    include/symbols/LogosSymbol.h
    src/application/CommandLine.cpp
    include/symbols/types/LogosBool.h
    include/symbols/types/LogosFloat.h
    include/symbols/types/LogosInt.h
    include/symbols/types/LogosString.h
    include/symbols/LogosType.h
    include/symbols/types/LogosVoid.h
    src/symbols/loops/LogosLoopVar.cpp
    include/symbols/loops/LogosLoopVar.h
    include/symbols/exprs/unary/LogosIterable.h
    include/symbols/exprs/unary/constants/LogosStringConst.h
    src/symbols/exprs/unary/constants/LogosStringConst.cpp
    src/symbols/funcs/LogosParam.cpp
    include/symbols/funcs/LogosParam.h
    src/symbols/exprs/unary/LogosMethodCall.cpp
    include/symbols/exprs/unary/LogosMethodCall.h
    src/symbols/exprs/unary/constants/LogosTypeConst.cpp
    include/symbols/exprs/unary/constants/LogosTypeConst.h
)

add_executable(logos main.cpp)

target_link_libraries(logos PRIVATE lib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libLLVM.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/liblldCommon.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/liblldMachO.dylib
)

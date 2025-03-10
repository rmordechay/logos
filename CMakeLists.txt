cmake_minimum_required(VERSION 3.22)
project(logos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/application
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/include/files
    ${CMAKE_CURRENT_SOURCE_DIR}/include/codegen
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sema
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols/exprs
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols/exprs/unary
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/include/loops
)

add_library(lib STATIC
    # headers
    include/application/Application.h
    include/application/ThreadPool.h
    include/codegen/CodeGenerator.h
    include/codegen/LogosLinker.h
    include/LogosError.h
    include/parser/LogosLexer.h
    include/parser/LogosParser.h
    include/sema/AntlrConverter.h
    include/sema/SemaAnalyser.h
    # Symbols headers
    include/symbols/exprs/binary/LogosBinaryExpr.h
    include/symbols/exprs/unary/constants/LogosConstant.h
    include/symbols/exprs/unary/constants/LogosStringConst.h
    include/symbols/exprs/unary/constants/LogosTypeConst.h
    include/symbols/exprs/unary/LogosArray.h
    include/symbols/exprs/unary/LogosArrayIndex.h
    include/symbols/exprs/unary/LogosFuncCall.h
    include/symbols/exprs/unary/LogosInstance.h
    include/symbols/exprs/unary/LogosIterable.h
    include/symbols/exprs/unary/LogosMethodCall.h
    include/symbols/exprs/unary/LogosSelection.h
    include/symbols/exprs/unary/LogosVariable.h
    include/symbols/funcs/LogosFunc.h
    include/symbols/funcs/LogosFuncImpl.h
    include/symbols/funcs/LogosMethodImpl.h
    include/symbols/funcs/LogosParam.h
    include/symbols/funcs/LogosPrint.h
    include/symbols/LogosSymbol.h
    include/symbols/LogosType.h
    include/symbols/loops/LogosForeachLoop.h
    include/symbols/loops/LogosLoopVar.h
    include/symbols/loops/LogosRangeLoop.h
    include/symbols/object/LogosField.h
    include/symbols/object/LogosObject.h
    include/symbols/stmts/LogosAssignment.h
    include/symbols/stmts/LogosIf.h
    include/symbols/stmts/LogosReturn.h
    include/symbols/stmts/LogosStmtBlock.h
    include/symbols/stmts/LogosVarDec.h
    include/symbols/types/LogosBool.h
    include/symbols/types/LogosFloat.h
    include/symbols/types/LogosInt.h
    include/symbols/types/LogosString.h
    include/symbols/types/LogosVoid.h
    include/cli/LogosCli.h
    include/cli/LogosCliCmd.h
    include/cli/LogosRunCmd.h

    # src
    src/application/Application.cpp
    src/application/ThreadPool.cpp
    src/cli/LogosCli.cpp
    src/codegen/CodeGenerator.cpp
    src/codegen/LogosLinker.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/sema/AntlrConverter.cpp
    src/sema/SemaAnalyser.cpp
    # Symbols src
    src/symbols/exprs/binary/LogosBinaryExpr.cpp
    src/symbols/exprs/unary/constants/LogosConstant.cpp
    src/symbols/exprs/unary/constants/LogosStringConst.cpp
    src/symbols/exprs/unary/constants/LogosTypeConst.cpp
    src/symbols/exprs/unary/LogosArray.cpp
    src/symbols/exprs/unary/LogosArrayIndex.cpp
    src/symbols/exprs/unary/LogosFuncCall.cpp
    src/symbols/exprs/unary/LogosInstance.cpp
    src/symbols/exprs/unary/LogosMethodCall.cpp
    src/symbols/exprs/unary/LogosSelection.cpp
    src/symbols/exprs/unary/LogosVariable.cpp
    src/symbols/funcs/LogosFunc.cpp
    src/symbols/funcs/LogosFuncImpl.cpp
    src/symbols/funcs/LogosMethodImpl.cpp
    src/symbols/funcs/LogosParam.cpp
    src/symbols/funcs/LogosPrint.cpp
    src/symbols/loops/LogosForeachLoop.cpp
    src/symbols/loops/LogosLoopVar.cpp
    src/symbols/loops/LogosRangeLoop.cpp
    src/symbols/object/LogosField.cpp
    src/symbols/object/LogosObject.cpp
    src/symbols/stmts/LogosAssignment.cpp
    src/symbols/stmts/LogosIf.cpp
    src/symbols/stmts/LogosReturn.cpp
    src/symbols/stmts/LogosStmtBlock.cpp
    src/symbols/stmts/LogosVarDec.cpp
    src/cli/LogosCli.cpp
    src/cli/LogosRunCmd.cpp
)

add_executable(lgs main.cpp)

target_link_libraries(lgs PRIVATE lib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libLLVM.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/liblldCommon.dylib
    ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/liblldMachO.dylib
)

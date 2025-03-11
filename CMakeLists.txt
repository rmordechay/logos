cmake_minimum_required(VERSION 3.22)
project(logos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    external/include
    external/include/antlr4-runtime
    include
    include/application
    include/cli
    include/files
    include/codegen
    include/analysis
    include/symbols
    include/symbols/exprs
    include/symbols/exprs/unary
    include/parser
    include/loops
)

add_library(lib STATIC
    # headers
    include/application/Logos.h
    include/application/ThreadPool.h
    include/codegen/CodeGenerator.h
    include/codegen/LogosLinker.h
    include/LogosError.h
    include/parser/LogosLexer.h
    include/parser/LogosParser.h
    include/analysis/AntlrConverter.h
    include/analysis/SemaAnalyser.h
    include/analysis/ProjectAnalyser.h
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
    include/symbols/stmts/LogosField.h
    include/symbols/types/LogosObject.h
    include/symbols/stmts/LogosAssignment.h
    include/symbols/stmts/LogosIf.h
    include/symbols/stmts/LogosReturn.h
    include/symbols/stmts/LogosStmtBlock.h
    include/symbols/stmts/LogosVarDec.h
    include/symbols/types/LogosBool.h
    include/symbols/types/LogosFloat.h
    include/symbols/types/LogosInt.h
    include/symbols/types/LogosStr.h
    include/symbols/types/LogosVoid.h
    include/cli/LogosCli.h
    include/cli/LogosRunCmd.h
    include/cli/LogosGenerateCmd.h
    include/analysis/LogosAnalyser.h

    # src
    src/application/Logos.cpp
    src/application/ThreadPool.cpp
    src/cli/LogosCli.cpp
    src/codegen/CodeGenerator.cpp
    src/codegen/LogosLinker.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/analysis/AntlrConverter.cpp
    src/analysis/SemaAnalyser.cpp
    src/analysis/ProjectAnalyser.cpp
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
    src/symbols/stmts/LogosField.cpp
    src/symbols/types/LogosObject.cpp
    src/symbols/stmts/LogosAssignment.cpp
    src/symbols/stmts/LogosIf.cpp
    src/symbols/stmts/LogosReturn.cpp
    src/symbols/stmts/LogosStmtBlock.cpp
    src/symbols/stmts/LogosVarDec.cpp
    src/cli/LogosCli.cpp
    src/cli/LogosRunCmd.cpp
    src/cli/LogosGenerateCmd.cpp
    src/symbols/types/LogosBool.cpp
    src/symbols/types/LogosInt.cpp
    src/symbols/types/LogosStr.cpp
    src/symbols/types/LogosVoid.cpp
    src/symbols/types/LogosFloat.cpp
)

add_executable(lgs main.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lgs PRIVATE lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libLLVM.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldCommon.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldMachO.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libantlr4-runtime.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(lgs PRIVATE lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libantlr4-runtime.so
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libLLVM.so
    )
endif()


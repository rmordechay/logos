cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")

include_directories(
    external/include
    external/include/antlr4-runtime
    include
    include/logos
    include/cli
    include/files
    include/codegen
    include/analysis
    include/symbols
    include/parser
)

add_library(lib STATIC
    # headers
    include/logos/Logos.h
    include/logos/LgsGlobals.h
    include/logos/ThreadPool.h
    include/files/LgsFile.h
    include/files/LgsInterfaceFile.h
    include/files/LgsMainFile.h
    include/files/LgsObjectFile.h
    include/logos/LgsData.h
    include/logos/LgsStack.h
    include/logos/LgsErrors.h
    include/codegen/CodeGenerator.h
    include/codegen/CodeGenMetadata.h
    include/codegen/LgsLinker.h
    include/parser/LogosLexer.h
    include/parser/LogosParser.h
    include/analysis/AntlrConverter.h
    include/analysis/LgsAnalyser.h
    include/analysis/SemaAnalyser.h
    include/analysis/ProjectAnalyser.h
    include/cli/LgsCli.h
    include/cli/LgsCmd.h
    include/cli/LgsRunCmd.h
    include/cli/LgsGenerateCmd.h

    # Symbols headers
    include/symbols/LgsValue.h
    include/symbols/LgsSymbol.h
    include/symbols/exprs/LgsNull.h
    include/symbols/exprs/LgsExpr.h
    include/symbols/exprs/binary/LgsBinaryExpr.h
    include/symbols/exprs/unary/LgsIterable.h
    include/symbols/exprs/unary/LgsArray.h
    include/symbols/exprs/unary/LgsArrayIndex.h
    include/symbols/exprs/unary/LgsFuncCall.h
    include/symbols/exprs/unary/LgsInstance.h
    include/symbols/exprs/unary/LgsSelection.h
    include/symbols/exprs/unary/LgsVariable.h
    include/symbols/exprs/unary/LgsUnaryExpr.h
    include/symbols/exprs/unary/constants/LgsConstExpr.h
    include/symbols/exprs/unary/constants/LgsStrConst.h
    include/symbols/exprs/unary/constants/LgsTypeConst.h
    include/symbols/exprs/unary/constants/LgsIntConst.h
    include/symbols/exprs/unary/constants/LgsFloatConst.h
    include/symbols/exprs/unary/constants/LgsBoolConst.h
    include/symbols/exprs/unary/constants/LgsCharConst.h
    include/symbols/funcs/LgsFunc.h
    include/symbols/funcs/LgsFuncImpl.h
    include/symbols/funcs/LgsMethodImpl.h
    include/symbols/funcs/LgsParam.h
    include/symbols/funcs/LgsPrint.h
    include/symbols/funcs/LgsFuncSignature.h
    include/symbols/types/LgsType.h
    include/symbols/loops/LgsForeachLoop.h
    include/symbols/loops/LgsRangeLoop.h
    include/symbols/stmts/LgsField.h
    include/symbols/stmts/LgsEnum.h
    include/symbols/stmts/LgsPatternMatching.h
    include/symbols/stmts/LgsAssignment.h
    include/symbols/stmts/LgsIfStmt.h
    include/symbols/stmts/LgsReturn.h
    include/symbols/stmts/LgsStmtBlock.h
    include/symbols/stmts/LgsVarDec.h
    include/symbols/types/LgsType.h
    include/symbols/types/LgsBool.h
    include/symbols/types/LgsFloat.h
    include/symbols/types/LgsInt.h
    include/symbols/types/LgsStr.h
    include/symbols/types/LgsVoid.h
    include/symbols/types/LgsChar.h
    include/symbols/types/LgsObject.h
    include/symbols/types/LgsInterface.h
    include/symbols/types/LgsArrayType.h

    # src
    src/logos/Logos.cpp
    src/logos/LgsStack.cpp
    src/logos/ThreadPool.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsRunCmd.cpp
    src/cli/LgsGenerateCmd.cpp
    src/codegen/CodeGenerator.cpp
    src/codegen/LgsLinker.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/analysis/AntlrConverter.cpp
    src/analysis/SemaAnalyser.cpp
    src/analysis/ProjectAnalyser.cpp

    # Symbols src
    src/symbols/LgsSymbol.cpp
    src/symbols/LgsValue.cpp
    src/symbols/exprs/LgsExpr.cpp
    src/symbols/exprs/binary/LgsBinaryExpr.cpp
    src/symbols/exprs/unary/constants/LgsStrConst.cpp
    src/symbols/exprs/unary/constants/LgsTypeConst.cpp
    src/symbols/exprs/unary/constants/LgsIntConst.cpp
    src/symbols/exprs/unary/constants/LgsFloatConst.cpp
    src/symbols/exprs/unary/constants/LgsBoolConst.cpp
    src/symbols/exprs/unary/constants/LgsCharConst.cpp
    src/symbols/exprs/unary/LgsArray.cpp
    src/symbols/exprs/unary/LgsArrayIndex.cpp
    src/symbols/exprs/unary/LgsFuncCall.cpp
    src/symbols/exprs/unary/LgsInstance.cpp
    src/symbols/exprs/unary/LgsSelection.cpp
    src/symbols/exprs/unary/LgsVariable.cpp
    src/symbols/funcs/LgsFunc.cpp
    src/symbols/funcs/LgsParam.cpp
    src/symbols/funcs/LgsPrint.cpp
    src/symbols/loops/LgsLoop.cpp
    src/symbols/loops/LgsForeachLoop.cpp
    src/symbols/loops/LgsRangeLoop.cpp
    src/symbols/stmts/LgsField.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/stmts/LgsAssignment.cpp
    src/symbols/stmts/LgsIfStmt.cpp
    src/symbols/stmts/LgsReturn.cpp
    src/symbols/stmts/LgsStmtBlock.cpp
    src/symbols/stmts/LgsVarDec.cpp
    src/symbols/stmts/LgsEnum.cpp
    src/symbols/stmts/LgsPatternMatching.cpp
    src/symbols/types/LgsBool.cpp
    src/symbols/types/LgsInt.cpp
    src/symbols/types/LgsStr.cpp
    src/symbols/types/LgsVoid.cpp
    src/symbols/types/LgsFloat.cpp
    src/symbols/types/LgsChar.cpp
    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsArrayType.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsObject.cpp
)

add_executable(lgs main.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lgs PRIVATE
        lib
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


enable_testing()
add_executable(lgs_tests
    tests/main.cpp
    tests/e2e/e2eTest.cpp
    tests/parser/ParserTest.cpp
    tests/analysis/sema/loops/SemaForeachLoopTests.cpp
    tests/analysis/sema/loops/SemaRangeLoopTests.cpp
    tests/analysis/sema/pattern_matching/SemaPatternMatchingTests.cpp
    tests/analysis/sema/enums/SemaEnumsTests.cpp
    tests/codegen/loops/CodegenRangeLoopTests.cpp
    tests/codegen/object/CodegenObjectTests.cpp
)

target_include_directories(lgs_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lgs_tests PRIVATE
        lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libgtest.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libgmock.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libgtest_main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libLLVM.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldCommon.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldMachO.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libantlr4-runtime.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(lgs PRIVATE
        lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libgtest.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libgtest_main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libantlr4-runtime.so
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libLLVM.so
    )
endif()

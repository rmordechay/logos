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
    include/data
    include/cli
    include/files
    include/codegen
    include/analysis
    include/symbols
    include/parser
    include/utils
)

add_library(lib STATIC
    # headers
    include/analysis/AntlrConverter.h
    include/analysis/SemaAnalyser.h
    include/cli/LgsCli.h
    include/cli/LgsCmd.h
    include/cli/LgsGenerateCmd.h
    include/cli/LgsRunCmd.h
    include/codegen/CodeGenerator.h
    include/codegen/CodeGenMetadata.h
    include/codegen/LgsLinker.h
    include/data/LgsData.h
    include/data/LgsErrors.h
    include/data/LgsWarnings.h
    include/files/LgsAppFile.h
    include/files/LgsEnvFile.h
    include/files/LgsFile.h
    include/files/LgsInterfaceFile.h
    include/files/LgsMainFile.h
    include/files/LgsObjectFile.h
    include/logos/LgsActiveEnv.h
    include/logos/Platform.h
    include/logos/LgsErrorHandler.h
    include/logos/LgsGlobals.h
    include/logos/LgsProject.h
    include/logos/LgsStack.h
    include/logos/Logos.h
    include/parser/LogosLexer.h
    include/parser/LogosParser.h
    include/utils/LgsC.h
    include/utils/ThreadPool.h

    # Symbols headers
    include/symbols/builtin/LgsPrint.h
    include/symbols/exprs/binary/LgsBinaryExpr.h
    include/symbols/exprs/LgsCast.h
    include/symbols/exprs/LgsExpr.h
    include/symbols/exprs/LgsNull.h
    include/symbols/exprs/unary/constants/LgsBoolConst.h
    include/symbols/exprs/unary/constants/LgsCharConst.h
    include/symbols/exprs/unary/constants/LgsConstExpr.h
    include/symbols/exprs/unary/constants/LgsFloatConst.h
    include/symbols/exprs/unary/constants/LgsIntConst.h
    include/symbols/exprs/unary/constants/LgsLongConst.h
    include/symbols/exprs/unary/constants/LgsStrConst.h
    include/symbols/exprs/unary/constants/LgsTypeConst.h
    include/symbols/exprs/unary/LgsIterIndex.h
    include/symbols/exprs/unary/LgsDArray.h
    include/symbols/exprs/unary/LgsEnumField.h
    include/symbols/exprs/unary/LgsFuncCall.h
    include/symbols/exprs/unary/LgsInstance.h
    include/symbols/exprs/unary/LgsSArray.h
    include/symbols/exprs/unary/LgsSelection.h
    include/symbols/exprs/unary/LgsUnaryExpr.h
    include/symbols/exprs/unary/LgsVariable.h
    include/symbols/exprs/unary/LgsHashMap.h
    include/symbols/exprs/unary/vectors/LgsVec2.h
    include/symbols/exprs/unary/vectors/LgsVec3.h
    include/symbols/exprs/unary/vectors/LgsVec4.h
    include/symbols/funcs/LgsFunc.h
    include/symbols/funcs/LgsFuncImpl.h
    include/symbols/funcs/LgsMethodImpl.h
    include/symbols/funcs/LgsParam.h
    include/symbols/LgsSymbol.h
    include/symbols/LgsValue.h
    include/symbols/loops/LgsForeachLoop.h
    include/symbols/loops/LgsRangeLoop.h
    include/symbols/stmts/LgsAssignment.h
    include/symbols/stmts/LgsBreakStmt.h
    include/symbols/stmts/LgsContinueStmt.h
    include/symbols/stmts/LgsField.h
    include/symbols/stmts/LgsIfStmt.h
    include/symbols/stmts/LgsPatternMatch.h
    include/symbols/stmts/LgsReturn.h
    include/symbols/stmts/LgsStmtBlock.h
    include/symbols/stmts/LgsVarDec.h
    include/symbols/types/LgsAny.h
    include/symbols/types/LgsArray.h
    include/symbols/types/LgsBool.h
    include/symbols/types/LgsChar.h
    include/symbols/types/LgsEnum.h
    include/symbols/types/LgsFloat.h
    include/symbols/types/LgsFuncType.h
    include/symbols/types/LgsInt.h
    include/symbols/types/LgsInterface.h
    include/symbols/types/LgsIterable.h
    include/symbols/types/LgsMethodType.h
    include/symbols/types/LgsObject.h
    include/symbols/types/LgsStr.h
    include/symbols/types/LgsType.h
    include/symbols/types/LgsVoid.h
    include/symbols/types/LgsLong.h
    include/symbols/types/LgsMap.h
    include/symbols/types/LgsPair.h
    include/symbols/types/LgsUnknownType.h
    include/symbols/types/LgsMapMethods.h
    include/symbols/types/LgsArrayMethods.h

    # src
    src/analysis/AntlrConverter.cpp
    src/analysis/SemaAnalyser.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsGenerateCmd.cpp
    src/cli/LgsRunCmd.cpp
    src/codegen/CodeGenerator.cpp
    src/codegen/LgsLinker.cpp
    src/logos/LgsErrorHandler.cpp
    src/logos/LgsProject.cpp
    src/logos/LgsStack.cpp
    src/logos/Logos.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/utils/LgsC.cpp
    src/utils/ThreadPool.cpp

    # Symbols src
    src/symbols/builtin/LgsPrint.cpp
    src/symbols/exprs/binary/LgsBinaryExpr.cpp
    src/symbols/exprs/LgsCast.cpp
    src/symbols/exprs/LgsExpr.cpp
    src/symbols/exprs/unary/constants/LgsBoolConst.cpp
    src/symbols/exprs/unary/constants/LgsCharConst.cpp
    src/symbols/exprs/unary/constants/LgsFloatConst.cpp
    src/symbols/exprs/unary/constants/LgsIntConst.cpp
    src/symbols/exprs/unary/constants/LgsSArray.cpp
    src/symbols/exprs/unary/constants/LgsStrConst.cpp
    src/symbols/exprs/unary/constants/LgsTypeConst.cpp
    src/symbols/exprs/unary/LgsIterIndex.cpp
    src/symbols/exprs/unary/LgsDArray.cpp
    src/symbols/exprs/unary/LgsEnumField.cpp
    src/symbols/exprs/unary/LgsFuncCall.cpp
    src/symbols/exprs/unary/LgsInstance.cpp
    src/symbols/exprs/unary/LgsSelection.cpp
    src/symbols/exprs/unary/LgsVariable.cpp
    src/symbols/exprs/unary/LgsHashMap.cpp
    src/symbols/funcs/LgsFunc.cpp
    src/symbols/funcs/LgsFuncImpl.cpp
    src/symbols/funcs/LgsMethodImpl.cpp
    src/symbols/funcs/LgsParam.cpp
    src/symbols/LgsSymbol.cpp
    src/symbols/LgsValue.cpp
    src/symbols/loops/LgsForeachLoop.cpp
    src/symbols/loops/LgsLoop.cpp
    src/symbols/loops/LgsRangeLoop.cpp
    src/symbols/stmts/LgsAssignment.cpp
    src/symbols/stmts/LgsBreakStmt.cpp
    src/symbols/stmts/LgsContinueStmt.cpp
    src/symbols/stmts/LgsField.cpp
    src/symbols/stmts/LgsIfStmt.cpp
    src/symbols/stmts/LgsPatternMatch.cpp
    src/symbols/stmts/LgsReturn.cpp
    src/symbols/stmts/LgsStmt.cpp
    src/symbols/stmts/LgsStmtBlock.cpp
    src/symbols/stmts/LgsVarDec.cpp
    src/symbols/types/LgsAny.cpp
    src/symbols/types/LgsArray.cpp
    src/symbols/types/LgsBool.cpp
    src/symbols/types/LgsChar.cpp
    src/symbols/types/LgsEnum.cpp
    src/symbols/types/LgsFloat.cpp
    src/symbols/types/LgsFuncType.cpp
    src/symbols/types/LgsInt.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsMethodType.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/types/LgsStr.cpp
    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsVoid.cpp
    src/symbols/types/LgsMap.cpp
    src/symbols/types/LgsUnknownType.cpp
    src/symbols/types/LgsLong.cpp
    src/symbols/exprs/unary/constants/LgsLongConst.cpp
    src/utils/DynArray.c
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libLLVM.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldCommon.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldMachO.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libantlr.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(ZLIB REQUIRED)
    target_link_libraries(lib PRIVATE
        ZLIB::ZLIB
        zstd
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libLLVM.so
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/liblldELF.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/liblldCommon.a
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/linux/libantlr.a
    )
endif()

add_executable(lgs main.cpp)
target_link_libraries(lgs PRIVATE lib)
#add_subdirectory(tests)

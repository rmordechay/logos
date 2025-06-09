cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")

set(SOURCE_FILES
    src/logos/Logos.cpp
    src/logos/LgsErrHandler.cpp
    src/logos/LgsProject.cpp
    src/logos/LgsRuntime.cpp
    src/logos/LgsStack.cpp
    src/analysis/AntlrConverter.cpp
    src/analysis/SemaAnalyser.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsFormatCmd.cpp
    src/cli/LgsGenerateCmd.cpp
    src/cli/LgsRunCmd.cpp
    src/codegen/CodeGenerator.cpp
    src/codegen/LgsLinker.cpp
    src/extern/LgsCLang.cpp
    src/extern/LgsCLangVisitor.cpp
    src/files/LgsMainFile.cpp
    src/files/LgsObjectFile.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/utils/LgsUtils.cpp
    src/utils/ThreadPool.cpp

    src/symbols/exprs/unary/constants/LgsBoolConst.cpp
    src/symbols/exprs/unary/constants/LgsCharConst.cpp
    src/symbols/exprs/unary/constants/LgsFloatConst.cpp
    src/symbols/exprs/unary/constants/LgsIntConst.cpp
    src/symbols/exprs/unary/constants/LgsLongConst.cpp
    src/symbols/exprs/unary/constants/LgsShortConst.cpp
    src/symbols/exprs/unary/constants/LgsStrConst.cpp
    src/symbols/exprs/unary/constants/LgsTypeConst.cpp
    src/symbols/exprs/unary/LgsArrayExpr.cpp
    src/symbols/exprs/unary/LgsEnumField.cpp
    src/symbols/exprs/unary/LgsFuncCall.cpp
    src/symbols/exprs/unary/LgsHashMap.cpp
    src/symbols/exprs/unary/LgsInstance.cpp
    src/symbols/exprs/unary/LgsIterIndex.cpp
    src/symbols/exprs/unary/LgsSelection.cpp
    src/symbols/exprs/unary/LgsVariable.cpp
    src/symbols/exprs/LgsBinaryExpr.cpp
    src/symbols/exprs/LgsCast.cpp
    src/symbols/exprs/LgsExpr.cpp
    src/symbols/funcs/LgsFunc.cpp
    src/symbols/funcs/LgsMainFunc.cpp
    src/symbols/funcs/LgsParam.cpp
    src/symbols/loops/LgsForLoop.cpp
    src/symbols/loops/LgsForeachLoop.cpp
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
    src/symbols/types/primitives/LgsBool.cpp
    src/symbols/types/primitives/LgsChar.cpp
    src/symbols/types/primitives/LgsFloat.cpp
    src/symbols/types/primitives/LgsInt.cpp
    src/symbols/types/primitives/LgsLong.cpp
    src/symbols/types/primitives/LgsShort.cpp
    src/symbols/types/primitives/LgsSize.cpp
    src/symbols/types/primitives/LgsVoid.cpp
    src/symbols/types/LgsAny.cpp
    src/symbols/types/LgsArray.cpp
    src/symbols/types/LgsEnum.cpp
    src/symbols/types/LgsFuncType.cpp
    src/symbols/types/LgsGroup.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsIterable.cpp
    src/symbols/types/LgsMap.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/types/LgsStr.cpp
    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsUnknownType.cpp
    src/symbols/LgsSymbol.cpp
    src/symbols/LgsValue.cpp
)

add_library(lib ${SOURCE_FILES})
target_precompile_headers(lib PRIVATE include/pch.h)
target_include_directories(lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(lib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libLLVM.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/libclang-cpp.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldCommon.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/macos/liblldMachO.dylib
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
# add_subdirectory(tests)

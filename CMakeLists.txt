cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(antlr4-runtime REQUIRED)
set(LLVM_LINK_LLVM_DYLIB ON)
set(CLANG_LINK_CLANG_DYLIB ON)
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

llvm_map_components_to_libnames(LLVM_LIBS
        support
        core
        irreader
        linker
        aarch64codegen
        asmparser
        asmprinter
        coroutines
        passes
        aarch64asmparser
        option
)

set(SOURCE_FILES
    src/utils/LgsErrHandler.cpp
    src/logos/LgsApp.cpp
    src/logos/LgsStack.cpp
    src/logos/LgsLinker.cpp
    src/analysis/AntlrConverter.cpp
    src/analysis/SemaAnalyser.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsFormatCmd.cpp
    src/cli/LgsGenerateCmd.cpp
    src/cli/LgsRunCmd.cpp
    src/extern/LgsCLang.cpp
    src/extern/LgsCLangVisitor.cpp
    src/files/LgsMainFile.cpp
    src/files/LgsObjectFile.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/utils/LgsUtils.cpp
    src/logos/LgsCodeGen.cpp
    src/files/LgsInterfaceFile.cpp

    src/symbols/LgsSymbol.cpp
    src/symbols/LgsValue.cpp
    src/symbols/LgsSymbolTable.cpp
    src/symbols/funcs/LgsCoroutine.cpp
    src/symbols/exprs/LgsBinaryExpr.cpp
    src/symbols/exprs/LgsExpr.cpp
    src/symbols/exprs/unary/LgsCast.cpp
    src/symbols/exprs/unary/constants/LgsBoolConst.cpp
    src/symbols/exprs/unary/constants/LgsCharConst.cpp
    src/symbols/exprs/unary/constants/LgsFloatConst.cpp
    src/symbols/exprs/unary/constants/LgsIntConst.cpp
    src/symbols/exprs/unary/constants/LgsLongConst.cpp
    src/symbols/exprs/unary/constants/LgsShortConst.cpp
    src/symbols/exprs/unary/constants/LgsStrConst.cpp
    src/symbols/exprs/unary/constants/LgsUIntConst.cpp
    src/symbols/exprs/unary/vectors/LgsVec2.cpp
    src/symbols/exprs/unary/vectors/LgsVec3.cpp
    src/symbols/exprs/unary/vectors/LgsVec4.cpp
    src/symbols/exprs/unary/LgsArrayExpr.cpp
    src/symbols/exprs/unary/LgsFuncCall.cpp
    src/symbols/exprs/unary/LgsHashMap.cpp
    src/symbols/exprs/unary/LgsInstance.cpp
    src/symbols/exprs/unary/LgsIterIndex.cpp
    src/symbols/exprs/unary/LgsSelection.cpp
    src/symbols/exprs/unary/LgsVariable.cpp
    src/symbols/exprs/unary/LgsPostfixExpr.cpp
    src/symbols/exprs/unary/LgsPrefixExpr.cpp
    src/symbols/funcs/LgsFunc.cpp
    src/symbols/funcs/LgsMainFunc.cpp
    src/symbols/funcs/LgsParam.cpp
    src/symbols/loops/LgsForLoop.cpp
    src/symbols/loops/LgsForeachLoop.cpp
    src/symbols/loops/LgsRangeLoop.cpp
    src/symbols/loops/LgsInfiniteLoop.cpp
    src/symbols/loops/LgsWhileLoop.cpp
    src/symbols/stmts/LgsAssignment.cpp
    src/symbols/stmts/LgsBreak.cpp
    src/symbols/stmts/LgsContinue.cpp
    src/symbols/stmts/LgsField.cpp
    src/symbols/stmts/LgsIfStmt.cpp
    src/symbols/stmts/LgsReturn.cpp
    src/symbols/stmts/LgsStmt.cpp
    src/symbols/stmts/LgsStmtsBlock.cpp
    src/symbols/stmts/LgsVarDec.cpp
    src/symbols/stmts/LgsDeferStmt.cpp
    src/symbols/types/primitives/LgsBool.cpp
    src/symbols/types/primitives/LgsChar.cpp
    src/symbols/types/primitives/LgsFloat.cpp
    src/symbols/types/primitives/LgsInt.cpp
    src/symbols/types/primitives/LgsLong.cpp
    src/symbols/types/primitives/LgsShort.cpp
    src/symbols/types/primitives/LgsSize.cpp
    src/symbols/types/LgsVoid.cpp
    src/symbols/types/LgsAny.cpp
    src/symbols/types/LgsDArray.cpp
    src/symbols/types/LgsSArray.cpp
    src/symbols/types/LgsEnum.cpp
    src/symbols/types/LgsFuncType.cpp
    src/symbols/types/LgsGroup.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsMap.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/types/LgsStr.cpp
    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsUnknownType.cpp
    src/symbols/types/primitives/LgsUInt.cpp
    src/symbols/types/LgsIterator.cpp
    src/symbols/types/LgsCPtr.cpp
    src/symbols/types/LgsNullable.cpp
)

add_library(lgs_core ${SOURCE_FILES})
target_include_directories(lgs_core PUBLIC
    include/external/include
    include/external/antlr4-runtime
    ${CLANG_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
)
target_link_libraries(lgs_core PUBLIC
    LLVM
    clang-cpp
    antlr4_shared
)

add_subdirectory(runtime)
target_precompile_headers(lgs_core PRIVATE include/pch.h)

add_executable(lgs main.cpp)
target_link_libraries(lgs PRIVATE lgs_core lgs_runtime)

add_subdirectory(tests)

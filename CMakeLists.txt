cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(antlr4-runtime REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Boost CONFIG REQUIRED context coroutine json)

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

set(CORE_SOURCES
    src/logos/LgsApp.cpp
    src/logos/LgsStack.cpp
    src/codegen/LgsLinker.cpp
    src/logos/LgsPaths.cpp
    src/analysis/LgsParserAdapter.cpp
    src/analysis/LgsSema.cpp
    src/analysis/LgsTypeResolver.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsCliCmd.cpp
    src/cli/LgsRunCmd.cpp
    src/cli/LgsAstCmd.cpp
    src/lgsc/LgsCLang.cpp
    src/lgsc/LgsCLangVisitor.cpp
    src/files/LgsMainFile.cpp
    src/files/LgsObjectFile.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/utils/LgsUtils.cpp
    src/codegen/LgsLLVM.cpp
    src/files/LgsInterfaceFile.cpp
    src/utils/LgsErrHandler.cpp

    src/symbols/LgsSymbol.cpp
    src/symbols/LgsSymbolTable.cpp
    src/symbols/LgsValue.cpp
    src/symbols/exprs/LgsExpr.cpp
    src/symbols/exprs/LgsUnaryExpr.cpp
    src/symbols/exprs/LgsBinaryExpr.cpp
    src/symbols/exprs/unary/LgsArrayExpr.cpp
    src/symbols/exprs/unary/LgsCast.cpp
    src/symbols/exprs/unary/LgsFuncCall.cpp
    src/symbols/exprs/unary/LgsHashMap.cpp
    src/symbols/exprs/unary/LgsInstance.cpp
    src/symbols/exprs/unary/LgsIterIndex.cpp
    src/symbols/exprs/unary/LgsPostfixExpr.cpp
    src/symbols/exprs/unary/LgsPrefixExpr.cpp
    src/symbols/exprs/unary/LgsSelection.cpp
    src/symbols/exprs/unary/LgsVariable.cpp
    src/symbols/exprs/unary/LgsVectorExpr.cpp
    src/symbols/exprs/unary/constants/LgsCharConst.cpp
    src/symbols/exprs/unary/constants/LgsFloatConst.cpp
    src/symbols/exprs/unary/constants/LgsIntConst.cpp
    src/symbols/exprs/unary/constants/LgsStrConst.cpp
    src/symbols/exprs/unary/constants/LgsUIntConst.cpp
    src/symbols/funcs/LgsCoroutine.cpp
    src/symbols/funcs/LgsFunc.cpp
    src/symbols/funcs/LgsMainFunc.cpp
    src/symbols/funcs/LgsParam.cpp
    src/symbols/loops/LgsForLoop.cpp
    src/symbols/loops/LgsForeachLoop.cpp
    src/symbols/loops/LgsInfiniteLoop.cpp
    src/symbols/loops/LgsRangeLoop.cpp
    src/symbols/loops/LgsWhileLoop.cpp
    src/symbols/stmts/LgsAssignment.cpp
    src/symbols/stmts/LgsBreak.cpp
    src/symbols/stmts/LgsContinue.cpp
    src/symbols/stmts/LgsDeferStmt.cpp
    src/symbols/stmts/LgsField.cpp
    src/symbols/stmts/LgsIfStmt.cpp
    src/symbols/stmts/LgsReturn.cpp
    src/symbols/stmts/LgsStmt.cpp
    src/symbols/stmts/LgsStmtsBlock.cpp
    src/symbols/stmts/LgsVarDec.cpp
    src/symbols/types/LgsAny.cpp
    src/symbols/types/LgsPtr.cpp
    src/symbols/types/LgsDArray.cpp
    src/symbols/types/LgsEnum.cpp
    src/symbols/types/LgsFuncType.cpp
    src/symbols/types/LgsGroup.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsIterator.cpp
    src/symbols/types/LgsMap.cpp
    src/symbols/types/LgsNullable.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/types/LgsSArray.cpp
    src/symbols/types/LgsStr.cpp
    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsUnknown.cpp
    src/symbols/types/LgsVec.cpp
    src/symbols/types/LgsVoid.cpp
    src/symbols/types/primitives/LgsBool.cpp
    src/symbols/types/primitives/LgsChar.cpp
    src/symbols/types/primitives/LgsDouble.cpp
    src/symbols/types/primitives/LgsFloat.cpp
    src/symbols/types/primitives/LgsInt.cpp
    src/symbols/types/primitives/LgsLong.cpp
    src/symbols/types/primitives/LgsShort.cpp
    src/symbols/types/primitives/LgsSize.cpp
    src/symbols/types/primitives/LgsUInt.cpp
    src/codegen/LgsCodeGen.cpp
    include/codegen/LgsCodeGen.h
    src/files/LgsTestFile.cpp
    include/files/LgsTestFile.h
)

set(RUNTIME_SOURCES
    runtime/lib/Lgs_hashmap.cpp
    runtime/lib/Lgs_array.cpp
    runtime/lib/Lgs_system.cpp
    runtime/lib/Lgs_defer.cpp
    runtime/lib/Lgs_runtime.cpp
    runtime/lib/Lgs_scheduler.cpp
    runtime/lib/Lgs_stack.cpp
    runtime/lib/Lgs_print.cpp
    include/logos/LgsAppConfigs.h
)

add_library(lgs_core SHARED ${CORE_SOURCES} ${RUNTIME_SOURCES})
target_link_libraries(lgs_core PUBLIC
    LLVM
    clang-cpp
    antlr4_shared
    Boost::context
    Boost::coroutine
    Boost::json
    SQLite::SQLite3
)

target_precompile_headers(lgs_core PRIVATE include/pch.h)
target_include_directories(lgs_core PUBLIC
    include
    include/external/include
    include/external/antlr4-runtime
    ${CLANG_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symbols
    ${CMAKE_CURRENT_SOURCE_DIR}/include/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/runtime/include
)

add_executable(lgs main.cpp)
target_link_libraries(lgs PRIVATE lgs_core)

add_subdirectory(tests)

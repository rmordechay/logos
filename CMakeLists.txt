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
    src/logos/LgsPaths.cpp
    src/codegen/LgsLinker.cpp
    src/codegen/LgsCodeGen.cpp
    src/codegen/LgsLLVMGen.cpp
    src/analysis/LgsParserAdapter.cpp
    src/analysis/LgsSema.cpp
    src/analysis/LgsTypeResolver.cpp
    src/files/LgsMainFile.cpp
    src/files/LgsTestFile.cpp
    src/files/LgsObjectFile.cpp
    src/files/LgsInterfaceFile.cpp
    src/parser/LogosLexer.cpp
    src/parser/LogosParser.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsCliCmd.cpp
    src/cli/LgsRunCmd.cpp
    src/cli/LgsAstCmd.cpp
    src/cli/LgsTestCmd.cpp
    src/lgsc/LgsCLang.cpp
    src/lgsc/LgsCLangVisitor.cpp
    src/utils/LgsUtils.cpp
    src/utils/LgsErrHandler.cpp

    src/symbols/LgsSymbol.cpp
    src/symbols/LgsSymbolTable.cpp
    src/symbols/LgsValue.cpp
    src/symbols/builtins/LgsPrint.cpp
    src/symbols/builtins/LgsTest.cpp
    src/symbols/exprs/LgsExpr.cpp
    src/symbols/exprs/LgsBinaryExpr.cpp
    src/symbols/exprs/LgsArrayExpr.cpp
    src/symbols/exprs/LgsCast.cpp
    src/symbols/exprs/LgsFuncCall.cpp
    src/symbols/exprs/LgsHashMap.cpp
    src/symbols/exprs/LgsInstance.cpp
    src/symbols/exprs/LgsIterIndex.cpp
    src/symbols/exprs/LgsPostfixExpr.cpp
    src/symbols/exprs/LgsPrefixExpr.cpp
    src/symbols/exprs/LgsSelection.cpp
    src/symbols/exprs/LgsVariable.cpp
    src/symbols/exprs/LgsVectorExpr.cpp
    src/symbols/exprs/LgsTypeExpr.cpp
    src/symbols/exprs/constants/LgsCharConst.cpp
    src/symbols/exprs/constants/LgsFloatConst.cpp
    src/symbols/exprs/constants/LgsIntConst.cpp
    src/symbols/exprs/constants/LgsStrConst.cpp
    src/symbols/exprs/constants/LgsUIntConst.cpp
    src/symbols/funcs/LgsCoroutine.cpp
    src/symbols/funcs/LgsFunc.cpp
    src/symbols/funcs/LgsMainFunc.cpp
    src/symbols/funcs/LgsParam.cpp
    src/symbols/loops/LgsForLoop.cpp
    src/symbols/loops/LgsForeachLoop.cpp
    src/symbols/loops/LgsInfiniteLoop.cpp
    src/symbols/loops/LgsRangeLoop.cpp
    src/symbols/loops/LgsWhileLoop.cpp
    src/symbols/loops/LgsForVariables.cpp
    src/symbols/stmts/LgsIOPair.cpp
    src/symbols/stmts/LgsIOStmt.cpp
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
    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsVoid.cpp
    src/symbols/types/LgsUnknown.cpp
    src/symbols/types/LgsAny.cpp
    src/symbols/types/LgsPtr.cpp
    src/symbols/types/LgsEnum.cpp
    src/symbols/types/LgsFuncType.cpp
    src/symbols/types/LgsGroup.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsNullable.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/types/LgsSubType.cpp
    src/symbols/types/iterables/LgsMap.cpp
    src/symbols/types/iterables/LgsDArray.cpp
    src/symbols/types/iterables/LgsSArray.cpp
    src/symbols/types/iterables/LgsStr.cpp
    src/symbols/types/iterables/LgsIterable.cpp
    src/symbols/types/iterables/LgsVec.cpp
    src/symbols/types/primitives/LgsBool.cpp
    src/symbols/types/primitives/LgsChar.cpp
    src/symbols/types/primitives/LgsDouble.cpp
    src/symbols/types/primitives/LgsFloat.cpp
    src/symbols/types/primitives/LgsInt.cpp
    src/symbols/types/primitives/LgsLong.cpp
    src/symbols/types/primitives/LgsShort.cpp
    src/symbols/types/primitives/LgsSize.cpp
    src/symbols/types/primitives/LgsUInt.cpp
    src/symbols/types/primitives/LgsByte.cpp
)

set(RUNTIME_SOURCES
    runtime/lib/Lgs_hashmap.cpp
    runtime/lib/Lgs_DArray.cpp
    runtime/lib/Lgs_system.cpp
    runtime/lib/Lgs_defer.cpp
    runtime/lib/Lgs_runtime.cpp
    runtime/lib/Lgs_scheduler.cpp
    runtime/lib/Lgs_stack.cpp
    runtime/lib/Lgs_print.cpp
    runtime/lib/Lgs_arena.cpp
    src/symbols/types/iterables/LgsSet.cpp
    include/symbols/types/iterables/LgsSet.h
    runtime/include/Lgs_set.h
    runtime/lib/Lgs_set.cpp
    runtime/include/Lgs_hashmap.h
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

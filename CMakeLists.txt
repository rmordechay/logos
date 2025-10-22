cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

set(LLVM_LINK_LLVM_DYLIB ON)
set(CLANG_LINK_CLANG_DYLIB ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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
    src/analysis/LgsSema.cpp
    src/analysis/LgsLinter.cpp
    src/analysis/LgsTypeResolver.cpp
    src/parser/LgsLexer.cpp
    src/parser/LgsParser.cpp
    src/parser/LgsJsonParser.cpp
    src/parser/LgsFormatter.cpp
    src/cli/LgsCli.cpp
    src/cli/LgsCliCmd.cpp
    src/cli/commands/LgsRunCmd.cpp
    src/cli/commands/LgsAstCmd.cpp
    src/cli/commands/LgsTestCmd.cpp
    src/cli/commands/LgsLinterCmd.cpp
    src/cli/commands/LgsFormatCmd.cpp
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
    src/symbols/exprs/LgsNull.cpp
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
    src/symbols/stmts/LgsSwitch.cpp

    src/symbols/types/LgsType.cpp
    src/symbols/types/LgsVoid.cpp
    src/symbols/types/LgsUnknown.cpp
    src/symbols/types/LgsAny.cpp
    src/symbols/types/LgsPtr.cpp
    src/symbols/types/LgsEnum.cpp
    src/symbols/types/LgsFuncType.cpp
    src/symbols/types/LgsInterface.cpp
    src/symbols/types/LgsNullable.cpp
    src/symbols/types/LgsObject.cpp
    src/symbols/types/LgsSubType.cpp
    src/symbols/types/LgsTypePair.cpp
    src/symbols/types/iterables/LgsMap.cpp
    src/symbols/types/iterables/LgsDArray.cpp
    src/symbols/types/iterables/LgsSet.cpp
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
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_hashmap.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_darray.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_system.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_runtime.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_stack.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_print.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_arena.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_set.cpp
    include/data/LgsCliErrors.h
    include/symbols/types/LgsGeneric.h
    src/symbols/types/LgsGeneric.cpp
    src/cli/commands/LgsGenerateCmd.cpp
    include/cli/commands/LgsGenerateCmd.h
)

add_library(lgs_lib SHARED ${CORE_SOURCES} ${RUNTIME_SOURCES})
set_target_properties(lgs_lib PROPERTIES OUTPUT_NAME "lgs")
target_link_libraries(lgs_lib PUBLIC LLVM clang-cpp)

target_precompile_headers(lgs_lib PRIVATE include/pch.h)
target_include_directories(lgs_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/symbols
    ${CMAKE_SOURCE_DIR}/runtime/include
    ${CLANG_INCLUDE_DIRS}
)

add_executable(lgs main.cpp)
target_link_libraries(lgs PRIVATE lgs_lib)

add_subdirectory(tests)

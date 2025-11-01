cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")
option(LOGOS_RELEASE "Build release version" OFF)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
set(LLVM_LINK_LLVM_DYLIB ON)
set(CLANG_LINK_CLANG_DYLIB ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install prefix" FORCE)
endif()

find_program(CCACHE_PROGRAM ccache )
if (CCACHE_PROGRAM AND NOT LOGOS_RELEASE)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

set(COMPILER_SOURCE
    src/logos/LgsApp.cpp
    src/logos/LgsStack.cpp
    src/logos/LgsPaths.cpp
    src/logos/LgsAppMetadata.cpp
    src/files/LgsMainFile.cpp
    src/files/LgsObjectFile.cpp
    src/files/LgsInterfaceFile.cpp
    src/files/LgsTestFile.cpp
    src/files/LgsEnvFile.cpp
    src/files/LgsAppConfigFile.cpp
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
    src/lgsc/LgsCLang.cpp
    src/lgsc/LgsCLangVisitor.cpp
    src/utils/LgsUtils.cpp
    src/utils/LgsErrHandler.cpp

    src/cli/LgsCli.cpp
    src/cli/LgsCliCmd.cpp
    src/cli/commands/LgsRunCmd.cpp
    src/cli/commands/LgsAstCmd.cpp
    src/cli/commands/LgsTestCmd.cpp
    src/cli/commands/LgsLinterCmd.cpp
    src/cli/commands/LgsFormatCmd.cpp
    src/cli/commands/LgsGenerateCmd.cpp

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
    src/symbols/loops/LgsLoopMetaVar.cpp
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
    src/symbols/types/LgsGeneric.cpp
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

set(RUNTIME_SOURCE
    runtime/lib/Lgs_Map.cpp
    runtime/lib/Lgs_DArray.cpp
    runtime/lib/Lgs_System.cpp
    runtime/lib/Lgs_Runtime.cpp
    runtime/lib/Lgs_Stack.cpp
    runtime/lib/Lgs_Print.cpp
    runtime/lib/Lgs_Arena.cpp
    runtime/lib/Lgs_Set.cpp
)

# Runtime
add_library(lgs_runtime SHARED ${RUNTIME_SOURCE})
set_target_properties(lgs_runtime PROPERTIES OUTPUT_NAME "lgs_runtime")
target_include_directories(lgs_runtime PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/symbols
    ${CMAKE_SOURCE_DIR}/runtime/include
)

# Compiler
add_library(lgs_compiler SHARED ${COMPILER_SOURCE})
set_target_properties(lgs_compiler PROPERTIES OUTPUT_NAME "lgs_compiler")
target_link_libraries(lgs_compiler PUBLIC LLVM clang-cpp lgs_runtime)

# Options
if(LOGOS_RELEASE)
    target_compile_options(lgs_compiler PRIVATE -O3 -DNDEBUG)
    target_compile_options(lgs_runtime PRIVATE -O3 -DNDEBUG)
    set_target_properties(lgs_compiler PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_target_properties(lgs_runtime PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    foreach(target lgs_compiler lgs_runtime)
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Werror
            -Wreturn-type
            -Wno-unused-parameter
            -Wno-unused-variable
        )
    endforeach()
endif()

# Include
target_include_directories(lgs_compiler PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)
target_include_directories(lgs_compiler SYSTEM PUBLIC
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

# Link
add_executable(lgs main.cpp)
target_link_libraries(lgs PRIVATE lgs_compiler)

if(NOT LOGOS_RELEASE)
    set_target_properties(lgs PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    if(UNIX AND NOT APPLE)
        target_link_options(lgs PRIVATE -s)
    endif()
    add_subdirectory(tests)
endif()

# Install
install(TARGETS lgs RUNTIME DESTINATION bin)
install(TARGETS lgs_compiler lgs_runtime LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

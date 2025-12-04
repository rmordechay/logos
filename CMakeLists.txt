cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")
option(LOGOS_RELEASE "Build release version" OFF)

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
set(LLVM_LINK_LLVM_DYLIB ON)
set(CLANG_LINK_CLANG_DYLIB ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install prefix" FORCE)
endif ()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM AND NOT LOGOS_RELEASE)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()

set(COMPILER_SOURCE
    ${CMAKE_SOURCE_DIR}/compiler/src/logos/LgsApp.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/logos/LgsStack.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/logos/LgsPaths.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/logos/LgsAppCache.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/logos/LgsPkgManager.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/codegen/LgsLinker.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/codegen/LgsCodeGen.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/codegen/LgsCgModule.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/analysis/LgsSema.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/analysis/LgsTypeResolver.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/tools/LgsLinter.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/tools/LgsFormatter.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/tools/LgsJsonParser.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/parser/LgsLexer.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/parser/LgsParser.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/lgsc/LgsCCompiler.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/lgsc/LgsCLangParser.cpp

    # Files
    ${CMAKE_SOURCE_DIR}/compiler/src/files/LgsMainFile.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/files/LgsObjectFile.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/files/LgsInterfaceFile.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/files/LgsTestFile.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/files/LgsEnvFile.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/files/LgsAppConfigFile.cpp

    # CLI
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/LgsCliHandler.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/LgsCliCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/lpm/LgsPkgCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/lpm/LgsInstallCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsRunCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsCompileCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsAstCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsTestCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsLinterCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsFormatCmd.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/cli/commands/LgsGenerateCmd.cpp

    # Symbols
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/LgsSymbol.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/LgsSymbolTable.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/LgsValue.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsBinaryExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsTernaryExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsArrayExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsCast.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsFuncCall.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsHashMap.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsInstance.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsIterIndex.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsPostfixExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsPrefixExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsSelection.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsMetaSelection.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsVariable.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsEnvVar.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsVectorExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsTypeExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/LgsMatrixExpr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/constants/LgsCharConst.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/constants/LgsFloatConst.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/constants/LgsIntConst.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/constants/LgsStrConst.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/exprs/constants/LgsUIntConst.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/funcs/LgsCoroutine.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/funcs/LgsFunc.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/funcs/LgsMainFunc.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/funcs/LgsParam.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/loops/LgsForLoop.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/loops/LgsForeachLoop.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/loops/LgsInfiniteLoop.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/loops/LgsRangeLoop.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/loops/LgsWhileLoop.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/loops/LgsMetaVar.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsIOPair.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsIOStmt.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsAssignment.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsBreak.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsContinue.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsDeferStmt.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsField.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsIfStmt.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsReturn.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsStmt.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsStmtsBlock.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsVarDec.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/stmts/LgsSwitch.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/builtins/LgsPrint.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/builtins/LgsTest.cpp

    # Types
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsType.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsUnknown.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsSelf.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsAny.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsPtr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsEnum.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsFuncType.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsInterface.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsObject.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsSubType.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsTypePair.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsGenericType.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/LgsJsonType.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsMap.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsDArray.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsSet.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsSArray.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsStr.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsIterable.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsVec.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsMatrix.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/iterables/LgsVariadic.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsBool.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsChar.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsDouble.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsFloat.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsInt.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsLong.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsShort.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsSize.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsUInt.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsULong.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsByte.cpp
    ${CMAKE_SOURCE_DIR}/compiler/src/symbols/types/primitives/LgsVoid.cpp
    compiler/src/symbols/exprs/LgsJson.cpp
    lib/include/Lgs_Runtime.h
)

set(LGS_LIB_SOURCE
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_HashMap.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_DArrayExpr.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_StrExpr.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_System.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_Runtime.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_Allocator.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_SetExpr.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_Helpers.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/Lgs_Reflection.cpp
    ${CMAKE_SOURCE_DIR}/lib/src/context/Lgs_Aarch64.cpp
)

set(SHARED_SOURCE
    ${CMAKE_SOURCE_DIR}/shared/src/LgsErrHandler.cpp
    ${CMAKE_SOURCE_DIR}/shared/src/LgsUtils.cpp
)

# Logos lib and shared
add_library(lgs_lib SHARED ${LGS_LIB_SOURCE})
add_library(lgs_shared STATIC ${SHARED_SOURCE})
set_target_properties(lgs_lib PROPERTIES OUTPUT_NAME "lgs")

# Compiler executable
add_executable(lgs main.cpp ${COMPILER_SOURCE})

# Includes
target_include_directories(lgs_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/include
    ${CMAKE_SOURCE_DIR}/compiler/include
)
target_include_directories(lgs PUBLIC
    ${CMAKE_SOURCE_DIR}/compiler/include
    ${CMAKE_SOURCE_DIR}/compiler/include/symbols
    ${CMAKE_SOURCE_DIR}/external/include
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)
target_include_directories(lgs_shared PUBLIC
    ${CMAKE_SOURCE_DIR}/shared/include
)
target_include_directories(lgs SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/external/include
    ${OPENSSL_INCLUDE_DIR}
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)

# Link
target_link_libraries(lgs_lib PRIVATE lgs_shared)
target_link_libraries(lgs PRIVATE
    lgs_shared
    lgs_lib
    LLVM
    clang-cpp
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Options
if (LOGOS_RELEASE)
    target_compile_options(lgs PRIVATE -O3 -DNDEBUG)
    target_compile_options(lgs_lib PRIVATE -O3 -DNDEBUG)
    set_target_properties(lgs PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_target_properties(lgs_lib PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
    if (UNIX AND NOT APPLE)
        target_link_options(lgs PRIVATE -s)
    endif ()
else ()
    target_compile_options(lgs PRIVATE -Wall -Wextra -Wpedantic -Wreturn-type -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function)
    add_subdirectory(tests)
endif ()

# Install
install(TARGETS lgs RUNTIME DESTINATION bin)
install(TARGETS lgs_lib LIBRARY DESTINATION lib)

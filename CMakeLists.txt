cmake_minimum_required(VERSION 3.22)
project(logos VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DLOGOS_VERSION="${CMAKE_PROJECT_VERSION}")
option(LOGOS_RELEASE "Build release version" OFF)

set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/external)
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
set(LLVM_LINK_LLVM_DYLIB ON)
set(CLANG_LINK_CLANG_DYLIB ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Install prefix" FORCE)
endif ()

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM AND NOT LOGOS_RELEASE)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()

set(LGS_SOURCE
    # Logos
    ${CMAKE_SOURCE_DIR}/src/logos/LgsApp.cpp
    ${CMAKE_SOURCE_DIR}/src/logos/LgsStack.cpp
    ${CMAKE_SOURCE_DIR}/src/logos/LgsPaths.cpp
    ${CMAKE_SOURCE_DIR}/src/logos/LgsAppCache.cpp
    ${CMAKE_SOURCE_DIR}/src/files/LgsMainFile.cpp
    ${CMAKE_SOURCE_DIR}/src/files/LgsObjectFile.cpp
    ${CMAKE_SOURCE_DIR}/src/files/LgsInterfaceFile.cpp
    ${CMAKE_SOURCE_DIR}/src/files/LgsTestFile.cpp
    ${CMAKE_SOURCE_DIR}/src/files/LgsEnvFile.cpp
    ${CMAKE_SOURCE_DIR}/src/files/LgsAppConfigFile.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/LgsLinker.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/LgsCodeGen.cpp
    ${CMAKE_SOURCE_DIR}/src/codegen/LgsLLVMGen.cpp
    ${CMAKE_SOURCE_DIR}/src/analysis/LgsSema.cpp
    ${CMAKE_SOURCE_DIR}/src/analysis/LgsTypeResolver.cpp
    ${CMAKE_SOURCE_DIR}/src/tools/LgsLinter.cpp
    ${CMAKE_SOURCE_DIR}/src/tools/LgsFormatter.cpp
    ${CMAKE_SOURCE_DIR}/src/tools/LgsJsonParser.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/LgsLexer.cpp
    ${CMAKE_SOURCE_DIR}/src/parser/LgsParser.cpp
    ${CMAKE_SOURCE_DIR}/src/lgsc/LgsCLang.cpp
    ${CMAKE_SOURCE_DIR}/src/lgsc/LgsCLangParser.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/LgsUtils.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/LgsErrHandler.cpp

    # CLI
    ${CMAKE_SOURCE_DIR}/src/cli/LgsCli.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/LgsCliCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsRunCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsCompileCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsAstCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsTestCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsLinterCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsFormatCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/commands/LgsGenerateCmd.cpp

    # Package manager
    ${CMAKE_SOURCE_DIR}/src/cli/lpm/LgsPkgCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/cli/lpm/LgsInstallCmd.cpp
    ${CMAKE_SOURCE_DIR}/src/logos/LgsPkgManager.cpp

    # Symbols
    ${CMAKE_SOURCE_DIR}/src/symbols/LgsSymbol.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/LgsSymbolTable.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/LgsValue.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/builtins/LgsPrint.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/builtins/LgsTest.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsBinaryExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsArrayExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsCast.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsFuncCall.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsHashMap.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsInstance.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsIterIndex.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsPostfixExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsPrefixExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsSelection.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsVariable.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsEnvVar.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsVectorExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsTypeExpr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/LgsNull.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/constants/LgsCharConst.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/constants/LgsFloatConst.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/constants/LgsIntConst.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/constants/LgsStrConst.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/exprs/constants/LgsUIntConst.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/funcs/LgsCoroutine.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/funcs/LgsFunc.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/funcs/LgsMainFunc.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/funcs/LgsParam.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/loops/LgsForLoop.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/loops/LgsForeachLoop.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/loops/LgsInfiniteLoop.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/loops/LgsRangeLoop.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/loops/LgsWhileLoop.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/loops/LgsMetaVar.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsIOPair.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsIOStmt.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsAssignment.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsBreak.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsContinue.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsDeferStmt.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsField.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsIfStmt.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsReturn.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsStmt.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsStmtsBlock.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsVarDec.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/stmts/LgsSwitch.cpp

    # Types
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsType.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsUnknown.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsAny.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsPtr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsEnum.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsFuncType.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsNullable.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsObject.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsSubType.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsTypePair.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/LgsGeneric.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsMap.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsDArray.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsSet.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsSArray.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsStr.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsIterable.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/iterables/LgsVec.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsBool.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsChar.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsDouble.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsFloat.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsInt.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsLong.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsShort.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsSize.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsUInt.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsByte.cpp
    ${CMAKE_SOURCE_DIR}/src/symbols/types/primitives/LgsVoid.cpp
)

set(RUNTIME_SOURCE
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Map.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_DArray.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_System.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Runtime.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Print.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Arena.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Set.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Scheduler.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/context/Lgs_Aarch64.cpp
    ${CMAKE_SOURCE_DIR}/runtime/lib/Lgs_Helpers.cpp
)

# Runtime
add_library(lgs_lib SHARED ${RUNTIME_SOURCE})
set_target_properties(lgs_lib PROPERTIES OUTPUT_NAME "lgs")

# Executable
add_executable(lgs main.cpp ${LGS_SOURCE})

# Includes
target_include_directories(lgs_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include/data
    ${CMAKE_SOURCE_DIR}/runtime/include
)
target_include_directories(lgs PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/symbols
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)
target_include_directories(lgs SYSTEM PUBLIC
    ${OPENSSL_INCLUDE_DIR}
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
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

# Link
target_link_libraries(lgs PRIVATE lgs_lib
    LLVM
    clang-cpp
    CURL::libcurl
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Install
install(TARGETS lgs RUNTIME DESTINATION bin)
install(TARGETS lgs_lib LIBRARY DESTINATION lib)

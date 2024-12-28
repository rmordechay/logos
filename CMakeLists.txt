cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a")
set(GTEST_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest.1.15.2.dylib")
set(GTEST_LIB_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest_main.1.15.2.dylib")
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/llvm")

file(GLOB GENERATED_SRC "${CMAKE_CURRENT_SOURCE_DIR}/logos/parser/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/logos/parser/*.h")

find_package(LLVM REQUIRED CONFIG)

add_executable(logos
    main.cpp
    ${GENERATED_SRC}
    logos/LogosConfigs.h
    logos/codegen/CodeGenerator.cpp
    logos/codegen/CodeGenerator.h
    logos/codegen/BuiltinFunc.cpp
    logos/codegen/BuiltinFunc.h
    logos/codegen/CodeNode.cpp
    logos/codegen/CodeNode.h
    logos/codegen/nodes/Add.cpp
    logos/codegen/nodes/Add.h
    logos/codegen/nodes/StoreInt.cpp
    logos/codegen/nodes/StoreInt.h
    logos/codegen/builtin/Print.cpp
    logos/codegen/builtin/Print.h
    logos/project/LogosFile.cpp
    logos/project/LogosFile.h
    logos/project/LogosPackage.cpp
    logos/project/LogosPackage.h
    logos/project/LogosProject.cpp
    logos/project/LogosProject.h
    logos/sema/LogosErrors.h
    logos/sema/Scope.cpp
    logos/sema/Scope.h
    logos/sema/SemAnalyser.cpp
    logos/sema/SemAnalyser.h
    logos/symbols/LogosSymbol.h
    logos/symbols/LogosTypedValue.h
    logos/symbols/types/LogosBool.cpp
    logos/symbols/types/LogosBool.h
    logos/symbols/types/LogosFloat.cpp
    logos/symbols/types/LogosFloat.h
    logos/symbols/types/LogosInt.cpp
    logos/symbols/types/LogosInt.h
    logos/symbols/types/LogosString.cpp
    logos/symbols/types/LogosString.h
    logos/symbols/logosOperator.h
    logos/symbols/exprs/LogosBinaryExpr.h
    logos/symbols/exprs/LogosExpr.h
    logos/symbols/exprs/LogosUnaryExpr.h
)

target_include_directories(logos PRIVATE
    logos
    logos/project
    logos/symbols
    logos/parser
    logos/codegen
    logos/sema
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${LLVM_INCLUDE_DIRS}
)

llvm_map_components_to_libnames(LLVM_LIBS core bitreader bitwriter support)
target_link_libraries(logos PRIVATE ${ANTLR_LIB} ${LLVM_LIBS} ${GTEST_LIB} ${GTEST_LIB_MAIN})

# Tests
enable_testing()

add_executable(logos_tests
    tests/ParserTest.cpp
)

target_include_directories(logos_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
)

target_link_libraries(logos_tests PRIVATE ${GTEST_LIB} ${GTEST_LIB_MAIN})

add_test(NAME LogosTests COMMAND logos_tests)
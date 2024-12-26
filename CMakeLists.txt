cmake_minimum_required(VERSION 3.30)
project(logos)

set(CMAKE_CXX_STANDARD 20)

set(ANTLR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/include/antlr4-runtime")
set(ANTLR_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libantlr4-runtime.a")
set(GTEST_LIB "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest.1.15.2.dylib")
set(GTEST_LIB_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/libgtest_main.1.15.2.dylib")
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/llvm")

file(GLOB GENERATED_SRC "logos/parser/*.cpp" "logos/parser/*.h")

find_package(LLVM REQUIRED CONFIG)

add_executable(logos
    main.cpp
    ${GENERATED_SRC}
    logos/project/LogosProject.cpp
    logos/project/LogosProject.h
    logos/project/LogosPackage.cpp
    logos/project/LogosPackage.h
    logos/project/LogosFile.cpp
    logos/project/LogosFile.h
    logos/sema/SemAnalyser.cpp
    logos/sema/SemAnalyser.h
    logos/sema/Symbol.cpp
    logos/sema/Symbol.h
    logos/codegen/CodeGenerator.cpp
    logos/codegen/CodeGenerator.h
    logos/LogosConfigs.h
    logos/sema/Scope.cpp
    logos/sema/Scope.h
    logos/sema/LogosValue.cpp
    logos/sema/LogosValue.h
)

target_include_directories(logos PRIVATE
    logos
    logos/project
    logos/parser
    logos/codegen
    logos/sema
    ${ANTLR_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/include
    ${LLVM_INCLUDE_DIRS}
)

llvm_map_components_to_libnames(LLVM_LIBS core)
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
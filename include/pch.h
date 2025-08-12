#pragma once

#include <antlr4-runtime/antlr4-runtime.h>
#include <fstream>
#include <stack>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cassert>
#include <unistd.h>
#include <thread>
#include <filesystem>
#include <queue>
#include <condition_variable>
#include <functional>
#include <sstream>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include "llvm/IR/Verifier.h"
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IRReader/IRReader.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>

#include <clang/Basic/Diagnostic.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/Tooling/Tooling.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/CompilerInstance.h>

using namespace std;
using namespace llvm;
namespace fs = std::filesystem;
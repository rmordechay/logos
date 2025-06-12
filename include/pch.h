#pragma once

#include <iostream>
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

#include <Token.h>
#include <json/json.hpp>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include "llvm/IR/Verifier.h"
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <clang/Driver/Compilation.h>
#include <clang/Driver/Driver.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Tooling/Tooling.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Basic/Diagnostic.h>
#include <lld/Common/Driver.h>

using namespace std;
using namespace filesystem;
using namespace nlohmann;
using namespace llvm;
using namespace antlr4;

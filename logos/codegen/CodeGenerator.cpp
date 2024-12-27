#include "CodeGenerator.h"

#include <gtest/internal/gtest-port.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Constants.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

using namespace llvm;

void CodeGenerator::generateCode() {
    LLVMContext context;
    const auto module = new Module("root", context);
    IRBuilder builder(context);

    const auto voidType = Type::getVoidTy(context);
    const auto funcType = FunctionType::get(voidType, false);
    const auto mainFunction = Function::Create(funcType, Function::ExternalLinkage, "main", module);
    const auto entry = BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entry);

    const auto a = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "a");
    const auto b = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "b");

    builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 10), a);
    builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 20), b);

    const auto aVal = builder.CreateLoad(Type::getInt32Ty(context), a, "aVal");
    const auto bVal = builder.CreateLoad(Type::getInt32Ty(context), b, "bval");

    const auto sum = builder.CreateAdd(aVal, bVal, "sum");
    const auto sumVar = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "sumVar");
    builder.CreateStore(sum, sumVar);

    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::getUnqual(builder.getInt8Ty()), true);
    const auto printfFunc = llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf", module);
    auto formatStr = builder.CreateGlobalStringPtr("%d\n");
    auto intValue = llvm::ConstantInt::get(builder.getInt32Ty(), 42);
    builder.CreateCall(printfFunc, {formatStr, intValue});

    builder.CreateRetVoid();

    module->print(outs(), nullptr);
    std::error_code EC;
    raw_fd_ostream textFile("../codegen/output.ll", EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    std::system("llc -filetype=obj -mtriple=arm64-apple-macos ../codegen/output.ll -o ../codegen/output.o");
    std::system("clang ../codegen/output.o -o ../codegen/output");
}

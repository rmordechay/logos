#include "CodeGenerator.h"

#include <gtest/internal/gtest-port.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Constants.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

void CodeGenerator::generateCode(const std::vector<CodeNode*>& codeNodes) {
    LLVMContext context;
    const auto module = new Module("root", context);
    IRBuilder builder(context);
    insertMain(context, builder, module);
    for (const auto& codeNode : codeNodes) {
        codeNode->generateCode(context, builder, module);
    }
    builder.CreateRetVoid();

    // module->print(outs(), nullptr);
    writeToFile(module);
    runBinary();
}

void CodeGenerator::insertMain(LLVMContext& context, IRBuilder<>& builder, Module* module) {
    const auto voidType = Type::getVoidTy(context);
    const auto funcType = FunctionType::get(voidType, false);
    const auto mainFunction = Function::Create(funcType, Function::ExternalLinkage, "main", module);
    const auto entry = BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entry);
}

void CodeGenerator::writeToFile(const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile("../codegen/output.ll", EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
}

void CodeGenerator::runBinary() {
    std::system("llc -filetype=obj -mtriple=arm64-apple-macos ../codegen/output.ll -o ../codegen/output.o");
    std::system("clang ../codegen/output.o -o ../codegen/output");
    std::system("../codegen/output");
}

void CodeGenerator::generateCodeDemo() {
    // const auto int32Ty = Type::getInt32Ty(context);
    // const auto a = builder.CreateAlloca(int32Ty);
    // const auto b = builder.CreateAlloca(int32Ty);
    //
    // builder.CreateStore(ConstantInt::get(int32Ty, 10), a);
    // builder.CreateStore(ConstantInt::get(int32Ty, 20), b);
    //
    // const auto aVal = builder.CreateLoad(int32Ty, a);
    // const auto bVal = builder.CreateLoad(int32Ty, b);
    //
    // const auto sum = builder.CreateAdd(aVal, bVal);
    // const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::getUnqual(builder.getInt8Ty()), true);
    // const auto printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
    // auto formatStr = builder.CreateGlobalStringPtr("%d\n");
    // builder.CreateCall(printfFunc, {formatStr, sum});
}

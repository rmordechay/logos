#include "CodeGenerator.h"

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

    // const auto funcType = FunctionType::get(Type::getInt32Ty(context), false);
    // const auto mainFunction = Function::Create(funcType, Function::ExternalLinkage, "main", module);
    // const auto entry = BasicBlock::Create(context, "entry", mainFunction);
    // builder.SetInsertPoint(entry);

    // const auto a = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "a");
    // const auto b = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "b");
    //
    // builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 10), a);
    // builder.CreateStore(ConstantInt::get(Type::getInt32Ty(context), 20), b);

    // auto a_val = builder.CreateLoad(Type::getInt32Ty(context), a, "a_val");
    // auto b_val = builder.CreateLoad(Type::getInt32Ty(context), b, "b_val");

    // const auto sum = builder.CreateAdd(a_val, b_val, "sum");
    // const auto sumVar = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "sumVar");
    // builder.CreateStore(sum, sumVar);


    // const auto func = FunctionType::get(IntegerType::getInt32Ty(context), PointerType::getUnqual(Type::getInt8Ty(context)));
    // const auto printfFunc = module->getOrInsertFunction("printf", func);
    // auto formatStr = builder.CreateGlobalStringPtr("a = %d, b = %d\n");
    // builder.CreateCall(printfFunc, {formatStr, a_val, b_val});

    module->print(outs(), nullptr);

    std::error_code EC;
    raw_fd_ostream textFile("../codegen/output.ll", EC, sys::fs::OF_None);
    if (EC) {
        errs() << "Error opening file: " << EC.message() << "\n";
        return;
    }

    delete module;
}

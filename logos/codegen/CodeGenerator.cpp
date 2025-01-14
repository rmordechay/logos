#include "CodeGenerator.h"

#include "RuntimeScope.h"

#include <iostream>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include "llvm/Target/TargetMachine.h"

void CodeGenerator::run(const vector<CodeNode*>& codeNodes) {
    const auto module = new Module("main", context);
    RuntimeScope scope;
    declareFunctions(module, &scope);
    insertFunction(module, "main", builder.getInt32Ty(), &scope);

    for (const auto &codeNode : codeNodes) {
        codeNode->builder = &builder;
        codeNode->context = &context;
        codeNode->module = module;
        codeNode->generateProlog(&scope);
        builder.CreateAlloca(builder.getInt32Ty(), builder.getInt32(2));
        codeNode->generateEpilog(&scope);
    }

    builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0));
    module->print(outs(), nullptr);
    // compileLLVM("../codegen/output.ll", "../codegen/output");
    runBinary(*module);
}

void CodeGenerator::declareFunctions(Module* module, RuntimeScope* scope) {
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::get(builder.getInt1Ty(), 0), true);
    scope->functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
}

void CodeGenerator::insertFunction(Module* module, const string& name, Type* rt, RuntimeScope* scope) {
    const auto mainFuncType = FunctionType::get(rt, false);
    const auto mainFunc = Function::Create(mainFuncType, Function::ExternalLinkage, name, module);
    const auto mainEntry = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(mainEntry);
    scope->currentFrame = mainFunc;
}

void CodeGenerator::runBinary(const Module& module) {
    std::error_code EC;
    raw_fd_ostream textFile("../codegen/output.ll", EC, sys::fs::OF_None);
    module.print(textFile, nullptr);
    std::system("clang -o ../codegen/output ../codegen/output.ll");
    std::system("../codegen/output");
}

void CodeGenerator::compileLLVM(const std::string& llvmFilePath, const std::string& outputFilePath) {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();


    const auto context = std::make_unique<LLVMContext>();
    const std::string errorMsg;
    auto buffer = MemoryBuffer::getFile(llvmFilePath, errorMsg.data());

    SMDiagnostic err;
    const auto module = parseIR(**buffer, err, *context);
    std::cout << module->getName().str() << std::endl;

    const auto targetTriple = sys::getProcessTriple();
    std::string targetError;
    const auto* target = TargetRegistry::lookupTarget(targetTriple, targetError);
    std::cout << targetTriple << std::endl;

    const auto options = TargetOptions();
    auto CPU = "generic";
    auto features = "";
    auto targetMachine = target->createTargetMachine(targetTriple, CPU, features, options, Reloc::PIC_);

    std::error_code EC;
    raw_fd_ostream dest("../codegen/output.o", EC, sys::fs::OF_None);
    if (EC) {
        errs() << "Error opening output file: " << EC.message() << "\n";
        return;
    }

    if (verifyModule(*module, &errs())) {
        errs() << "Module verification failed!\n";
        return;
    }

    legacy::PassManager pass;
    auto fileType = CodeGenFileType::ObjectFile;
    if (targetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)) {
        errs() << "Target machine can't emit object file!\n";
        return;
    }
    pass.run(*module);
    dest.flush();
}


#include "CodeGenerator.h"

#include <iostream>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/TargetSelect.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include "llvm/Target/TargetMachine.h"

void CodeGenerator::run() {
    const auto module = new Module("main", context);
    declareFunctions(module);
    insertMain(module);
    map<string, Value*> symbolTable;
    builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0));
    module->print(outs(), nullptr);
    writeToFile(module);
    // compileLLVM("../codegen/output.ll", "../codegen/output");
    runBinary();
}

void CodeGenerator::declareFunctions(Module* module) {
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::get(builder.getInt1Ty(), 0), true);
    functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
}

void CodeGenerator::insertMain(Module* module) {
    const auto mainFuncType = FunctionType::get(builder.getInt32Ty(), false);
    const auto mainFunc = Function::Create(mainFuncType, Function::ExternalLinkage, "main", module);
    const auto mainEntry = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(mainEntry);
}

void CodeGenerator::writeToFile(const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile("../codegen/output.ll", EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
}

void CodeGenerator::runBinary() {
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


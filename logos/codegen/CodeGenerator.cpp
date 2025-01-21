#include "CodeGenerator.h"

#include "application/LogosPackage.h"
#include "application/LogosUtils.h"
#include "files/LogosObjectFile.h"

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
#include "llvm/Passes/PassBuilder.h"

#include <iostream>
#include <llvm/Linker/Linker.h>

const auto PRINT_IR_FILE = "../codegen/print.ll";
const auto LINKED_OBJECT_FILE = "../output.o";
const auto LINKED_IR_FILE = "../output.ll";
constexpr auto LLVM_OBJECT_FILE = CodeGenFileType::ObjectFile;

void CodeGenerator::run(const map<string, LogosFile*>& files) {
    LogosStack theStack;
    theStack.push(LogosStackFrame());

    for (auto [name, file] : files) {
        file->initModule(builder, theStack);
    }

    for (auto [name, file] : files) {
        auto module = file->generateModule(builder, theStack);
        modules.push_back(module);
    }
    const auto linker = linkModules();
    runBinary();
    delete linker;
    // generateTest();
}

Linker* CodeGenerator::linkModules() const {
    const auto rootModule = Utils::createLLVMModuleFromFile(PRINT_IR_FILE, builder.getContext(), *targetMachine);
    rootModule->print(outs(), nullptr);
    std::cout << "\n-----\n" << std::endl;
    const auto linker = new Linker(*rootModule);

    for (int i = 0; i < modules.size(); ++i) {
        const auto module = modules[i];
        module->print(outs(), nullptr);
        std::cout << "\n-----\n" << std::endl;
        linker->linkInModule(std::unique_ptr<Module>(module));
    }
    if (verifyModule(*rootModule, &errs())) {
        return linker;
    }
    std::error_code EC;
    raw_fd_ostream dest(LINKED_OBJECT_FILE, EC, sys::fs::OF_None);
    auto emitPass = legacy::PassManager();
    targetMachine->addPassesToEmitFile(emitPass, dest, nullptr, LLVM_OBJECT_FILE);
    emitPass.run(*rootModule);
    return linker;
}

void CodeGenerator::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();

    std::string targetError;
    const auto targetTriple = sys::getProcessTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, targetError);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), Reloc::PIC_);
}

void CodeGenerator::runBinary() {
    std::system("clang ../output.o -o ../output");
    std::system("../output");
}

void CodeGenerator::generateTest() {
    LLVMContext context;
    auto builder = IRBuilder(context);
    const std::vector<Type *> elements = {
        Type::getInt32Ty(context), Type::getFloatTy(context)
    };
    StructType *myStructType = StructType::create(context, elements, "MyStruct");
    AllocaInst *structInstance = builder.CreateAlloca(myStructType, nullptr, "myStructInstance");
    Value *fieldAPtr = builder.CreateStructGEP(myStructType, structInstance, 0, "a_ptr");

}

CodeGenerator::~CodeGenerator() {
    delete targetMachine;

}

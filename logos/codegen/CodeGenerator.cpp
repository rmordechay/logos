#include "CodeGenerator.h"

#include "LogosUtils.h"
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

void CodeGenerator::run(const LogosPackage* rootPackage) {
    initLLVM();
    LLVMContext context;
    vector<Module*> modules;
    auto builder = IRBuilder(context);
    generatePackage(rootPackage, modules, builder);
    auto linker = linkModules(modules, context);
    runBinary();
    // generateTest();
}

void CodeGenerator::generatePackage(const LogosPackage* package, vector<Module*>& modules, IRBuilder<>& builder) {
    for (const auto file : package->files) {
        auto module = file->generateModule(*targetMachine, builder);
        module->print(outs(), nullptr);
        std::cout << "\n-----\n" << std::endl;
        modules.push_back(module);
    }
    for (const auto innerPackage : package->packages) {
        generatePackage(innerPackage, modules, builder);
    }
}

Linker* CodeGenerator::linkModules(const vector<Module*>& modules, LLVMContext& context) const {
    const auto rootModule = Utils::createLLVMModuleFromFile(PRINT_IR_FILE, context, *targetMachine);
    rootModule->print(outs(), nullptr);
    std::cout << "\n-----\n" << std::endl;
    const auto linker = new Linker(*rootModule);

    for (int i = 0; i < modules.size(); ++i) {
        linker->linkInModule(std::unique_ptr<Module>(modules[i]));
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
    auto targetTriple = sys::getProcessTriple();
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

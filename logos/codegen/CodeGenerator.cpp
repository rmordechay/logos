#include "CodeGenerator.h"

#include "application/LogosUtils.h"
#include "files/LogosObjectFile.h"
#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

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

const auto LOGOS_LIB_IR_FILE = "../codegen/print.ll";
const auto LINKED_OBJECT_FILE = "../output.o";
const auto LINKED_IR_FILE = "../output.ll";
constexpr auto LLVM_OBJECT_FILE = CodeGenFileType::ObjectFile;

void CodeGenerator::run(const vector<LogosFile*>& files) {
    initLLVM();
    LogosStack theStack;
    const auto rootModule = Utils::createLLVMModuleFromFile(LOGOS_LIB_IR_FILE, builder.getContext(), *targetMachine);
    declareBuiltinFuncs(theStack, rootModule);
    for (const auto file : files) {
        file->initModule(builder, theStack);
    }

    for (const auto file : files) {
        auto module = file->generateModule(builder, theStack);
        modules.push_back(module);
    }

    // runBinary();
    // delete linker;
    // generateTest();
}

void CodeGenerator::declareBuiltinFuncs(LogosStack& theStack, Module* const rootModule) {
    theStack.globalFuncs["print"] = logosPrint.getLLVMValue(&builder, &theStack, rootModule);
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
    std::system("cd ../codegen && clang Main.ll MyObject.ll Print.ll -o ../output");
    std::system("../output");
}

void CodeGenerator::generateTest() {
    LLVMContext context;
    auto builder = IRBuilder(context);
    const std::vector<Type *> elements = {
        Type::getInt32Ty(context),
        Type::getFloatTy(context),
    };
    StructType *myStructType = StructType::create(context, elements, "MyStruct");
    AllocaInst *structInstance = builder.CreateAlloca(myStructType, nullptr, "myStructInstance");
    Value *fieldAPtr = builder.CreateStructGEP(myStructType, structInstance, 0, "a_ptr");
}

void CodeGenerator::emitLLVMFile(const string& filePath, const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
}

CodeGenerator::~CodeGenerator() {
    delete targetMachine;
}

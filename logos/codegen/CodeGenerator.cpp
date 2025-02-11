#include "CodeGenerator.h"

#include "application/LogosUtils.h"
#include "files/LogosMainFile.h"
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

void CodeGenerator::run(const map<string, LogosFile*>& files, LogosStack& theStack) {
    theStack.globalSymbols["print"] = LogosSymbol(FUNC, new LogosPrint());

    const auto module = new Module(LOGOS_MAIN_FILE, builder.getContext());
    const auto metadata = CodeGenMetadata{.builder = &builder, .theStack = &theStack, .module = module};
    const auto mainFile = dynamic_cast<LogosMainFile*>(files.at(LOGOS_MAIN_FILE));
    generateMainModule(mainFile, metadata);
    runBinary();
}

void CodeGenerator::generateMainModule(const LogosMainFile* mainFile, CodeGenMetadata metadata) {
    mainFile->mainFunc->getLLVMValue(&metadata);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    for (const auto func : mainFile->funcs) {
        func->getLLVMValue(&metadata);
    }
    writeIRToFile(metadata.module, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateObjModule(const LogosObject* obj, IRBuilder<>* builder, const LogosStack* theStack) {
    const auto module = new Module(obj->name(), builder->getContext());
    auto logosStack = *theStack;
    while (logosStack.size() > 1) {
        logosStack.pop();
    }

    auto newMetadata = CodeGenMetadata{.builder = builder, .theStack = &logosStack, .module = module};
    for (const auto func : obj->fields) {
        func->getLLVMValue(&newMetadata);
    }
    for (const auto func : obj->funcs) {
        func->getLLVMValue(&newMetadata);
    }

    writeIRToFile(newMetadata.module, module->getName().str());
}

void CodeGenerator::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
}

void CodeGenerator::runBinary() {
    std::system("cd ../codegen && clang Main.ll MyObject.ll Print.ll -o ../output");
    std::system("../output");
}

void CodeGenerator::generateTest() {
    LLVMContext context;
    auto builder = IRBuilder(context);
    const std::vector<Type*> elements = {Type::getInt32Ty(context), Type::getFloatTy(context),};
    StructType* myStructType = StructType::create(context, elements, "MyStruct");
    AllocaInst* structInstance = builder.CreateAlloca(myStructType, nullptr, "myStructInstance");
    Value* fieldAPtr = builder.CreateStructGEP(myStructType, structInstance, 0, "a_ptr");
}

void CodeGenerator::emitLLVMFile(const string& filePath, const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
}

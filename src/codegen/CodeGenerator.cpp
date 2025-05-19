#include "CodeGenerator.h"

#include "LgsConfig.h"
#include "Logos.h"
#include "Platform.h"
#include "funcs/LgsFuncImpl.h"
#include "funcs/LgsMethodImpl.h"
#include <LgsMainFile.h>
#include <ranges>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>

void CodeGenerator::generate(LgsMainFile* mainFile) {
    init();
    const auto module = createEmptyModule(LOGOS_MAIN_FILE_NAME);
    auto metadata = CodeGenMetadata{.module = module};
    for (const auto& func : mainFile->getAllFuncs()) {
        func->generateIRCode(&metadata);
    }
    generateMainFunc(&metadata, mainFile->mainFunc);
}

void CodeGenerator::generateMainFunc(CodeGenMetadata* metadata, LgsFuncImpl* mainFunc) {
    createIRMainFunc(metadata);
    metadata->lgsStack.enterScope(mainFunc);
    mainFunc->startBlock(metadata, mainFunc->entryBlock);
    mainFunc->stmtBlock->createIRValue(metadata);
    if (mainFunc->funcType.rt->isVoid) {
        metadata->builder.CreateRetVoid();
    }
    metadata->lgsStack.exitScope();
    metadata->builder.CreateRet(metadata->builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(metadata->module, LOGOS_MAIN_FILE_NAME);
}

void CodeGenerator::generateObjModule(const LgsType* obj) {
    const auto objName = obj->prettyName();
    if (IRModules.find(objName) != IRModules.end()) return;
    auto metadata = CodeGenMetadata{.module = createEmptyModule(objName)};
    for (const auto& overload : obj->getAllMethods()) {
        overload->generateIRCode(&metadata);
    }
    writeIRToFile(metadata.module, objName);
}

void CodeGenerator::createIRMainFunc(const CodeGenMetadata* metadata) {
    const auto mainFuncType = FunctionType::get(i32Ty, {i32Ty, ptrTy}, false);
    const auto mainFunc = Function::Create(mainFuncType, Function::ExternalLinkage, LOGOS_MAIN_FUNC, metadata->module);
    auto args = mainFunc->arg_begin();
    args++->setName("argc");
    args->setName("argv");
}

Module* CodeGenerator::createEmptyModule(const string& objName) {
    const auto module = new Module(objName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    IRModules[objName] = module;
    return module;
}

void CodeGenerator::init() {
    if (exists(paths.buildDir)) remove_all(paths.buildDir);
    create_directories(paths.buildDir);
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
    string error;
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
}

void CodeGenerator::writeIRToFile(const Module* module, const path& name) {
    if constexpr (WRITE_IR_TO_FILE) {
        const auto filePath = (paths.buildDir / name).string() + ".ll";
        std::error_code EC;
        raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
        module->print(textFile, nullptr);
    }
    if constexpr (DEBUG) {
        module->print(outs(), nullptr);
        std::cout << "\n-----\n\n";
    }
}
#include "CodeGenerator.h"
#include "Logos.h"
#include "funcs/LgsFuncImpl.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsVarDec.h"
#include <LgsMainFile.h>
#include <ranges>
#include <llvm/Support/FileSystem.h>
#include "llvm/ADT/ScopeExit.h"
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>

void CodeGenerator::generate(LgsMainFile* mainFile, const bool writeToFile) {
    initLLVM();
    createBuildDir();
    const auto module = createEmptyModule(LOGOS_MAIN_FILE_NAME);
    auto metadata = CodeGenMetadata{.module = module};

    for (const auto& func : mainFile->getAllFuncs()) {
        func->generateIRCode(&metadata);
    }
    mainFile->mainFunc->generateIRCode(&metadata);
    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));

    if (writeToFile) {
        writeIRToFile(metadata.module, LOGOS_MAIN_FILE_NAME);
    }
}

void CodeGenerator::generateObjModule(const LgsType* obj, const bool writeToFile) {
    const auto objName = obj->getName();
    if (IRModules.find(objName) != IRModules.end()) return;
    auto metadata = CodeGenMetadata{.module = createEmptyModule(objName)};
    for (const auto& overload : obj->getAllMethods()) {
        overload->generateIRCode(&metadata);
    }

    if (writeToFile) {
        writeIRToFile(metadata.module, objName);
    }
}

Module* CodeGenerator::createEmptyModule(const string& objName) {
    const auto module = new Module(objName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    IRModules[objName] = module;
    return module;
}

void CodeGenerator::initLLVM() {
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

void CodeGenerator::createBuildDir() {
    if (exists(paths.buildDir)) {
        remove_all(paths.buildDir);
    }
    create_directories(paths.buildDir);
}

void CodeGenerator::writeIRToFile(const Module* module, const path& name){
    const auto filePath = (paths.buildDir / name).string() + ".ll";
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
    std::cout << "\n-----\n\n";
}
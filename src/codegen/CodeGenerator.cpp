#include "CodeGenerator.h"
#include "funcs/LgsFuncImpl.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

#include <LgsMainFile.h>
#include <ranges>
#include <llvm/Support/FileSystem.h>
#include "llvm/ADT/ScopeExit.h"
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>

void CodeGenerator::generateMainModule(const path& buildDir, const LgsMainFile* mainFile, const bool writeToFile) {
    initLLVM();
    create_directories(buildDir);
    const auto module = createEmptryModule(LOGOS_MAIN_FILE_NAME);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};

    for (const auto& func : mainFile->funcs) {
        func->createIRValue(&metadata);
    }
    mainFile->mainFunc->createIRValue(&metadata);
    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));

    if (writeToFile) {
        writeIRToFile(metadata.currentModule, buildDir, LOGOS_MAIN_FILE_NAME);
    }
}

void CodeGenerator::generateObjModule(const path& buildDir, LgsType* obj, const bool writeToFile) {
    if (modules.find(obj->getName()) == modules.end()) return;
    const auto objName = obj->getName();
    const auto module = createEmptryModule(objName);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};

    for (const auto& [_, method] : obj->methods) {
        for (const auto& overload : method) {
            overload->createIRValue(&metadata);
        }
    }

    if (writeToFile) {
        writeIRToFile(metadata.currentModule, buildDir, objName);
    }
}

Module* CodeGenerator::createEmptryModule(const string& objName) {
    const auto module = new Module(objName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    modules[objName] = module;
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

void CodeGenerator::writeIRToFile(const Module* module, const path& buildDir, const path& name){
    const auto filePath = (buildDir / name).string() + ".ll";
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
    std::cout << "\n-----\n\n";
}

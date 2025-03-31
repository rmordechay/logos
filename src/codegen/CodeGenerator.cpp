#include "CodeGenerator.h"
#include "funcs/LgsFuncImpl.h"
#include "types/LgsObject.h"

#include <LgsMainFile.h>
#include <ranges>
#include <llvm/Support/FileSystem.h>
#include "llvm/ADT/ScopeExit.h"


void CodeGenerator::generateModule(const path& buildDir, const LgsMainFile* mainFile, const bool writeToFile) {
    const auto module = createEmptryModule(LOGOS_MAIN_FILE);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};

    for (const auto& func : mainFile->funcs) {
        func->createIRValue(&metadata);
    }
    mainFile->mainFunc->createIRValue(&metadata);
    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));

    if (writeToFile) {
        writeIRToFile(metadata.currentModule, buildDir, LOGOS_MAIN_FILE);
    }
}

void CodeGenerator::generateModule(const path& buildDir, LgsObject* obj, const bool writeToFile) {
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

void CodeGenerator::writeIRToFile(const Module* module, const path& buildDir, const path& name){
    const auto filePath = (buildDir / name).string() + ".ll";
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
    std::cout << "\n-----\n\n";
}

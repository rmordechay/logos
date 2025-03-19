#include "CodeGenerator.h"
#include "funcs/LgsFuncImpl.h"
#include <ranges>
#include <llvm/Support/FileSystem.h>

void CodeGenerator::generateModule(const path& buildDir, const LgsMainFile* mainFile, LgsGlobals* globals) {
    const auto module = createModule(LOGOS_MAIN_FILE);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};
    metadata.logosStack.globals = globals;

    for (const auto& func : mainFile->funcs) {
        func->createIRValue(&metadata);
    }
    mainFile->mainFunc->createIRValue(&metadata);

    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(metadata.currentModule, buildDir, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateModule(const path& buildDir, LgsObject* obj, LgsGlobals* globalSymbols) {
    const auto objName = obj->getName();
    const auto module = createModule(objName);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};
    metadata.logosStack.globals = globalSymbols;

    for (const auto& [_, method] : obj->methods) {
        method->createIRValue(&metadata);
    }
    writeIRToFile(metadata.currentModule, buildDir, objName);
}

Module* CodeGenerator::createModule(const string& objName) {
    const auto module = new Module(objName, context);
    const auto targetTriple = sys::getDefaultTargetTriple();
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

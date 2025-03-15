#include "CodeGenerator.h"
#include "funcs/LgsFuncImpl.h"
#include <ranges>
#include <llvm/Support/FileSystem.h>

void CodeGenerator::generateCode(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols) {
    create_directories(buildDir);
    initLLVM();
    generateModule(mainFile, globalSymbols);
}

void CodeGenerator::generateModule(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols) {
    const auto module = createModule(LOGOS_MAIN_FILE);
    auto metadata = CodeGenMetadata{.currentModule = module};
    metadata.logosStack.globalSymbols = globalSymbols;

    for (const auto& func : mainFile->funcs) {
        func->getIRValue(&metadata);
    }
    mainFile->mainFunc->getIRValue(&metadata);

    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(metadata.currentModule, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateModule(LgsObject* obj, const map<string, LgsSymbol>& globalSymbols) {
    const auto objName = obj->getName();
    const auto module = createModule(objName);
    auto metadata = CodeGenMetadata{.currentModule = module};
    metadata.logosStack.globalSymbols = globalSymbols;

    for (const auto& [_, method] : obj->methods) {
        method->getIRValue(&metadata);
    }
    writeIRToFile(metadata.currentModule, objName);
}

Module* CodeGenerator::createModule(const string& objName) {
    const auto module = new Module(objName, context);
    const auto targetTriple = sys::getDefaultTargetTriple();
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    modules[objName] = module;
    return module;
}

void CodeGenerator::writeIRToFile(const Module* module, const path& name){
    const auto filePath = (buildDir / name).string() + ".ll";
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
    std::cout << "\n-----\n\n";
}

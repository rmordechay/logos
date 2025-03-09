#include "CodeGenerator.h"

#include "funcs/LogosFuncImpl.h"
#include "object/LogosField.h"

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <ranges>
#include <llvm/Support/FileSystem.h>

using LogosGlobals = const std::map<std::string, LogosSymbol>&;

void CodeGenerator::generateCode(const map<string, LogosSymbol>& globalSymbols) const {
    create_directories(LOGOS_BUILD_DIR);
    generateMainModule(globalSymbols);
}

void CodeGenerator::generateMainModule(const map<string, LogosSymbol>& globalSymbols) const {
    const auto module = createModule(LOGOS_MAIN_FILE);
    auto metadata = CodeGenMetadata{.currentModule = module};
    metadata.logosStack.globalSymbols = globalSymbols;

    for (const auto& func : mainFile->funcs) {
        func->writeIRValue(&metadata);
    }
    mainFile->mainFunc->writeIRValue(&metadata);

    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(metadata.currentModule, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateObjectModule(LogosObject* obj, LogosGlobals globalSymbols) {
    const auto objName = obj->getName();
    const auto module = createModule(objName);
    auto metadata = CodeGenMetadata{.currentModule = module};
    metadata.logosStack.globalSymbols = globalSymbols;

    obj->getIRType();
    for (const auto& [name, field] : obj->fields) {
        metadata.logosStack.addGlobalSymbol(name, LogosSymbol(FIELD, field));
    }
    for (const auto& [_, method] : obj->methods) {
        method->writeIRValue(&metadata);
    }

    writeIRToFile(metadata.currentModule, objName);
    std::cout << "\n-----\n\n";
}

Module* CodeGenerator::createModule(const string& objName) {
    const auto module = new Module(objName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    modules[objName] = module;
    return module;
}

void CodeGenerator::writeIRToFile(const Module* module, const string& name) {
    std::error_code EC;
    raw_fd_ostream textFile(LOGOS_BUILD_DIR + name + ".ll", EC, sys::fs::OF_None);
    module->print(outs(), nullptr);
    module->print(textFile, nullptr);
}

void CodeGenerator::initIR() {
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

void CodeGenerator::emitIRFile(const string& filePath, const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
}

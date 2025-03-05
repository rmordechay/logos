#include "CodeGenerator.h"

#include "funcs/LogosFuncImpl.h"
#include "object/LogosField.h"

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <ranges>

using LogosGlobals = const std::map<std::string, LogosSymbol>&;

void CodeGenerator::generateCode(const map<string, LogosSymbol>& globalSymbols) const {
    create_directories(LOGOS_BUILD_DIR);
    generateMainModule(globalSymbols);
}

void CodeGenerator::generateMainModule(const map<string, LogosSymbol>& globalSymbols) const {
    const auto module = new Module(LOGOS_MAIN_FILE, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    modules[LOGOS_MAIN_FILE] = module;

    auto metadata = CodeGenMetadata{.currentModule = module};
    metadata.logosStack.globalSymbols = globalSymbols;

    // Funcs
    for (const auto& func : mainFile->funcs) {
        func->writeIRValue(&metadata);
    }

    // Main func
    mainFile->mainFunc->writeIRValue(&metadata);
    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(metadata.currentModule, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateObjModule(LogosObject* obj, LogosGlobals globalSymbols) {
    const auto objName = obj->name();
    const auto module = new Module(objName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    modules[objName] = module;

    auto metadata = CodeGenMetadata{.currentModule = module};
    metadata.logosStack.globalSymbols = globalSymbols;

    // Init struct
    obj->getIRType();

    // Fields
    for (const auto& [name, field] : obj->fields) {
        metadata.logosStack.addGlobalSymbol(name, LogosSymbol(FIELD, field));
    }

    // Funcs
    for (const auto& [_, val] : obj->funcs) {
        val->writeIRValue(&metadata);
    }

    writeIRToFile(metadata.currentModule, objName);
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

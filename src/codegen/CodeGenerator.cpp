#include "CodeGenerator.h"

#include "funcs/LogosFuncImpl.h"

#include <ranges>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/FileSystem.h>

using LogosGlobals = const std::map<std::string, LogosSymbol>&;

void CodeGenerator::generateCode(const LogosMainFile* mainFile, const map<string, LogosSymbol>& globalSymbols) {
    init();
    generateModule(mainFile, globalSymbols);
}

void CodeGenerator::generateModule(const LogosMainFile* mainFile, const map<string, LogosSymbol>& globalSymbols) const {
    const auto module = createModule(LOGOS_MAIN_FILE);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};
    metadata.logosStack.globalSymbols = globalSymbols;

    for (const auto& func : mainFile->funcs) {
        func->createIRValue(&metadata);
    }
    mainFile->mainFunc->createIRValue(&metadata);

    metadata.builder.CreateRet(metadata.builder.getInt32(EXIT_SUCCESS));
    writeIRToFile(metadata.currentModule, buildDir, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateModule(LogosObject* obj, const map<string, LogosSymbol>& globalSymbols, const path& buildDir) {
    const auto objName = obj->getName();
    const auto module = createModule(objName);
    auto metadata = CodeGenMetadata{.currentModule = module, .buildDir = buildDir};
    metadata.logosStack.globalSymbols = globalSymbols;

    for (const auto& [_, method] : obj->methods) {
        method->createIRValue(&metadata);
    }
    writeIRToFile(metadata.currentModule, buildDir, objName);
}

Module* CodeGenerator::createModule(const string& objName) {
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

void CodeGenerator::init() {
    create_directories(buildDir);
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
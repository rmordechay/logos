#include "codegen/CodeGenerator.h"
#include "logos/LgsConfig.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include <files/LgsMainFile.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>

void CodeGenerator::generate(const LgsMainFile* mainFile) {
    init();
    const auto module = createEmptyModule(LOGOS_MAIN_FILE_NAME);
    for (const auto [_, func] : mainFile->funcs) {
        func->generateIRCode(module);
    }
    mainFile->mainFunc->generateIRCode(module);
    writeIRToFile(module, LOGOS_MAIN_FILE_NAME);
}

void CodeGenerator::generateObjModule(const LgsType* obj) {
    const auto objName = obj->prettyName();
    if (IRModules.find(objName) != IRModules.end()) return;
    const auto module = createEmptyModule(objName);
    for (const auto& [_, method] : obj->methods) {
        method->generateIRCode(module);
    }
    writeIRToFile(module, objName);
}

Module* CodeGenerator::createEmptyModule(const string& objName) {
    const auto module = new Module(objName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    IRModules[objName] = module;
    return module;
}

void CodeGenerator::init() {
    // Build dir
    if (exists(paths.buildDir)) remove_all(paths.buildDir);
    create_directories(paths.buildDir);
    // LLVM
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

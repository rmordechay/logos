#include "CodeGenerator.h"

#include "funcs/LogosPrint.h"
#include "funcs/LogosUserFunc.h"
#include "object/LogosField.h"

#include <llvm/Support/TargetSelect.h>

void CodeGenerator::generateCode() const {
    generateMainModule();
}

void CodeGenerator::generateMainModule() const {
    auto builder = IRBuilder(context);
    const auto module = new Module(LOGOS_MAIN_FILE, context);
    logosStack.modules[LOGOS_MAIN_FILE] = module;
    auto metadata = createMetadata(builder, &logosStack, module);

    const auto mainFile = dynamic_cast<LogosMainFile*>(files.at(LOGOS_MAIN_FILE));
    // Main func
    mainFile->mainFunc->computeIRValue(&metadata);
    metadata.builder->CreateRet(metadata.builder->getInt32(EXIT_SUCCESS));
    // Funcs
    for (const auto& func : mainFile->funcs) {
        func->computeIRValue(&metadata);
    }

    writeIRToFile(metadata.module, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateObjModule(LogosObject* obj, CodeGenMetadata& metadata) {
    auto builder = IRBuilder(context);
    const auto objName = obj->name();
    const auto module = new Module(objName, context);
    metadata.logosStack->modules[objName] = module;
    const auto newStack = metadata.logosStack;
    newStack->reset();

    metadata.logosStack = newStack;

    obj->getIRType();
    for (const auto& entry : obj->fields) {
        entry.second->writeIRValue(&metadata);
    }

    for (const auto& entry : obj->funcs) {
        entry.second->writeIRValue(&metadata);
    }

    writeIRToFile(metadata.module, module->getName().str());
}

void CodeGenerator::writeIRToFile(const Module* module, const string& name) {
    std::error_code EC;
    raw_fd_ostream textFile(LOGOS_BUILD_DIR + name + ".ll", EC, sys::fs::OF_None);
    module->print(outs(), nullptr);
    module->print(textFile, nullptr);
}

CodeGenMetadata CodeGenerator::createMetadata(IRBuilder<>& builder, LogosStack* logosStack, Module* module) {
    return CodeGenMetadata{.builder = &builder, .logosStack = logosStack, .module = module};
}

void CodeGenerator::initIR() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
}

void CodeGenerator::emitIRFile(const string& filePath, const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
}

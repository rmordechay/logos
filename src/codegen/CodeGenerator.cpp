#include "codegen/CodeGenerator.h"
#include "logos/LgsConfig.h"
#include "logos/LgsRuntime.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include "utils/LgsUtils.h"

void CodeGenerator::init(const LgsPaths& paths) {
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
    dataLayout = getTargetMachine()->createDataLayout();
}

void CodeGenerator::writeIRToFile(map<string, Module*>& IRModules, LgsPaths& paths) {
    for (const auto [_, module] : IRModules) {
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildDir / module->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
        if (logLevel == DEBUG) {
            module->print(outs(), nullptr);
            lgsLog("\n-----\n\n");
        }
    }
}

#include "codegen/CodeGenerator.h"
#include "logos/LgsConfig.h"
#include "logos/LgsModule.h"
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

void CodeGenerator::writeIRToFile(map<string, LgsModule*>& modules, LgsPaths& paths) {
    for (const auto [_, module] : modules) {
        if (verifyModule(*module->IRModule, &errs())) {
            errs().flush();
            return;
        }
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildDir / module->IRModule->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->IRModule->print(textFile, nullptr);
        }
        if (logLevel == DEBUG) {
            module->IRModule->print(outs(), nullptr);
            lgsLog("\n-----\n\n");
        }
    }
}

#include "codegen/CodeGenerator.h"
#include "logos/LgsConfig.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include "utils/LgsUtils.h"

void CodeGenerator::init() {
    // Build dir
    if (exists(application.paths.buildDir)) remove_all(application.paths.buildDir);
    create_directories(application.paths.buildDir);
    // LLVM
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
    application.platform.dataLayout = getTargetMachine()->createDataLayout();
}

void CodeGenerator::writeIRToFile(LgsProject& project) {
    for (const auto [_, module] : project.IRModules) {
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (application.paths.buildDir / module->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
        if (application.logLevel == DEBUG) {
            module->print(outs(), nullptr);
            lgsLog("\n-----\n\n");
        }
    }
}

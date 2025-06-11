#include "codegen/CodeGenerator.h"
#include "files/LgsInterfaceFile.h"
#include "logos/LgsConfig.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include "utils/LgsUtils.h"
#include "utils/ThreadPool.h"

void CodeGenerator::generate(LogosProject& project) {
    init();
    ThreadPool threadPool;
    threadPool.start();
    for (const auto file : project.files) {
        threadPool.runTask([file, &project] {
            const auto module = file->generateIR(project);
            if (!module) return;
            lock_guard lock(mtx);
            project.IRModules[file->name] = module;
        });
    }
    threadPool.wait();
    writeIRToFile(project);
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
    platform.dataLayout = getTargetMachine()->createDataLayout();
}

void CodeGenerator::writeIRToFile(LogosProject& project) {
    for (const auto [_, module] : project.IRModules) {
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildDir / module->getName().str()).string() + ".ll";
            std::error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            module->print(textFile, nullptr);
        }
        if constexpr (DEBUG) {
            module->print(outs(), nullptr);
            std::cout << "\n-----\n\n";
        }
    }
}

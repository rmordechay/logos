#include "codegen/CodeGenerator.h"
#include "files/LgsInterfaceFile.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include "utils/ThreadPool.h"

#include <llvm/Support/TargetSelect.h>

void CodeGenerator::generate(const LogosProject* project) {
    init();
    ThreadPool threadPool;
    threadPool.start();
    for (const auto file : project->files) {
        threadPool.runTask([&file] {
            file->generateIR();
        });
    }
    threadPool.wait();
    writeIRToFile();
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
}

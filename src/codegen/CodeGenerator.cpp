#include "codegen/CodeGenerator.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include "utils/ThreadPool.h"

#include <files/LgsMainFile.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/MC/TargetRegistry.h>

void CodeGenerator::generate(const vector<LgsFile*>& files) {
    init();
    ThreadPool threadPool;
    threadPool.start();
    for (const auto file : files) {
        threadPool.runTask([=, &file] {
            file->generateIR();
        });
    }
    threadPool.wait();
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

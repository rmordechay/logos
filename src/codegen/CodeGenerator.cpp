#include "codegen/CodeGenerator.h"
#include "files/LgsInterfaceFile.h"
#include "logos/Logos.h"
#include "logos/Platform.h"
#include <llvm/Support/TargetSelect.h>

void CodeGenerator::generate(LogosProject& project) {
    init();
    for (const auto file : project.files) {
        file->generateIR(project);
    }
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
}

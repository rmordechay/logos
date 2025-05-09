#include "codegen/LgsLinker.h"
#include "CodeGenMetadata.h"
#include "Logos.h"
#include "Platform.h"
#include <LgsDefinitions.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FileSystem.h>
#include "llvm/IR/Verifier.h"
#include <iostream>
#include <unistd.h>

void generateObjFile(Module* module) {
    error_code ec;
    raw_fd_ostream fileStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);

    ModuleAnalysisManager analysisManager;
    PassBuilder passBuilder(targetMachine);
    ModulePassManager passManager;
    passBuilder.registerModuleAnalyses(analysisManager);
    const auto result = passBuilder
        .buildInlinerPipeline(OptimizationLevel::O2, ThinOrFullLTOPhase::FullLTOPostLink)
        .run(*module, analysisManager);

    fileStream.flush();
    fileStream.close();
}

bool LgsLinker::link() const {
    setPlatform(paths.objFilePath, paths.execFilePath);
    Module* mainModule = IRModules.find(LOGOS_MAIN_FILE_NAME)->second;
    Linker linker(*mainModule);

    for (const auto& path : STD_LIBS) {
        linkStdlib(path, &linker);
    }

    for (const auto& [name, module] : IRModules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        linker.linkInModule(std::unique_ptr<Module>(module));
    }

    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        std::cerr << ec.message() << endl;
        return false;
    }

    pass.run(*mainModule);
    outputStream.flush();
    outputStream.close();

    const auto linkerOpts = platform.linkerOpts;
    if (!platform.link(linkerOpts, outs(), errs(), false, false)) {
        errs().flush();
        return false;
    }
    return true;
}

void LgsLinker::linkStdlib(const string& path, Linker* linker) const {
    SMDiagnostic EC;
    auto module = parseIRFile(path, EC, context);
    assert(module);
    if (verifyModule(*module, &errs())) {
        errs().flush();
        return;
    }
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    linker->linkInModule(std::move(module));
}
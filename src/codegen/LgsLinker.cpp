#include "codegen/LgsLinker.h"
#include "CodeGenMetadata.h"
#include <CodeGenerator.h>
#include <LgsData.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FileSystem.h>
#include "llvm/IR/Verifier.h"

#include <iostream>

void LgsLinker::link(const std::map<std::string, Module*>& modules) const {
    Module* mainModule = modules.find(LOGOS_MAIN_FILE)->second;
    Linker linker(*mainModule);

    for (const auto& path : paths) {
        linkStdlib(path, &linker);
    }
    
    for (const auto& [name, file] : modules) {
        if (name == LOGOS_MAIN_FILE) continue;
        linker.linkInModule(std::unique_ptr<Module>(file));
    }

    if (verifyModule(*mainModule, &errs())) return;

    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(objFilePath.c_str(), ec, sys::fs::OF_None);
    targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    pass.run(*mainModule);
    outputStream.flush();
    lld::macho::link(getLinkerOpts(), outs(), errs(), false, false);
}

void LgsLinker::linkStdlib(const string& path, Linker* linker) const {
    SMDiagnostic EC;
    auto module = parseIRFile(path, EC, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    linker->linkInModule(std::move(module));
}

vector<const char*> LgsLinker::getLinkerOpts() const {
    return {
        DEFAULT_LINKER,
        objFilePath.c_str(),
        "-o", execFilePath.c_str(),
        "-lSystem",
        "-syslibroot", LIB_ROOT,
        "-e", ENTRY_POINT,
        "-platform_version", OS_NAME, PLATFORM_VERSION, PLATFORM_VERSION,
        "-arch", ARCH_NAME,
    };
}

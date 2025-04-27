#include "codegen/LgsLinker.h"
#include "CodeGenMetadata.h"
#include "Logos.h"

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
#include "lld/Common/Driver.h"

LLD_HAS_DRIVER(macho)
LLD_HAS_DRIVER(elf)

bool LgsLinker::link(const std::map<std::string, Module*>& modules) const {
    Module* mainModule = modules.find(LOGOS_MAIN_FILE_NAME)->second;
    Linker linker(*mainModule);

    for (const auto& path : stdlibPaths) {
        linkStdlib(path, &linker);
    }
    
    for (const auto& [name, module] : modules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        linker.linkInModule(std::unique_ptr<Module>(module));
    }

    if (verifyModule(*mainModule, &errs())) return false;

    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths->objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        std::cerr << ec.message() << endl;
        return false;
    }
    pass.run(*mainModule);
    outputStream.flush();
    return getLinkFunc();
}

bool LgsLinker::getLinkFunc() const {
    const bool linkingPassed = LINK_FUNC;
    if (!linkingPassed) {
        errs() << "Linking failed.";
        return false;
    }
    return true;
}

void LgsLinker::linkStdlib(const string& path, Linker* linker) const {
    SMDiagnostic EC;
    auto module = parseIRFile(path, EC, context);
    if (verifyModule(*module, &errs())) return;
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    linker->linkInModule(std::move(module));
}

vector<const char*> LgsLinker::getLinkerOpts() const {
    return {
        DEFAULT_LINKER,
        paths->objFilePath.c_str(),
        "-o", paths->execFilePath.c_str(),
        "-lSystem",
        "-syslibroot", LIB_ROOT,
        "-e", ENTRY_POINT,
        "-platform_version", OS_NAME, PLATFORM_VERSION, PLATFORM_VERSION,
        "-arch", ARCH_NAME,
    };
}

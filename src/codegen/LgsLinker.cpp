#include "codegen/LgsLinker.h"
#include <CodeGenerator.h>
#include <LgsGlobals.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FileSystem.h>

void LgsLinker::link(const std::map<std::string, Module*>& modules) const {
    auto stdlibModule = getStdlibModule();
    const auto mainModule = modules.find(LOGOS_MAIN_FILE)->second;
    Linker linker(*mainModule);
    linker.linkInModule(unique_ptr(std::move(stdlibModule)));
    for (const auto& [name, file] : modules) {
        if (name == LOGOS_MAIN_FILE) continue;
        linker.linkInModule(unique_ptr<Module>(std::move(file)));
    }

    error_code EC;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(objFilePath.c_str(), EC, sys::fs::OF_None);
    targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    pass.run(*mainModule);
    outputStream.flush();

    lld::macho::link(getLinkerOpts(), outs(), errs(), false, false);
}

std::unique_ptr<Module> LgsLinker::getStdlibModule() const {
    SMDiagnostic EC;
    std::unique_ptr<Module> stdlibModule = parseIRFile(LOGOS_STDLIB, EC, context);
    const auto targetTriple = sys::getDefaultTargetTriple();
    stdlibModule->setTargetTriple(targetTriple);
    stdlibModule->setDataLayout(targetMachine->createDataLayout());
    return stdlibModule;
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


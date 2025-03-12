#include "codegen/LogosLinker.h"
#include <CodeGenerator.h>
#include "LogosDefinitions.h"
#include <LogosMetadata.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Verifier.h>


namespace lld::macho {
    bool link(ArrayRef<const char *> argsArr, raw_ostream &stdoutOS, raw_ostream &stderrOS, bool exitEarly, bool disableOutput);
}

std::unique_ptr<Module> LogosLinker::getStdlibModule() {
    SMDiagnostic EC;
    std::unique_ptr<Module> stdlibModule = parseIRFile(LOGOS_STDLIB, EC, context);
    stdlibModule->setTargetTriple(targetTriple);
    stdlibModule->setDataLayout(targetMachine->createDataLayout());
    return stdlibModule;
}

void LogosLinker::link(const std::map<std::string, Module*>& modules) {
    auto stdlibModule = getStdlibModule();
    const auto mainModule = modules.find(LOGOS_MAIN_FILE)->second;

    Linker linker(*mainModule);
    linker.linkInModule(unique_ptr(std::move(stdlibModule)));
    for (const auto& [name, file] : modules) {
        if (name == LOGOS_MAIN_FILE) continue;
        linker.linkInModule(unique_ptr<Module>(std::move(file)));
    }

    writeExecFile(unique_ptr<Module>(mainModule));
    lld::macho::link(getLinkerOpts(), outs(), errs(), false, false);
}

void LogosLinker::writeExecFile(const unique_ptr<Module>& module) const {
    error_code EC;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(objectFilePath, EC, sys::fs::OF_None);
    targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    pass.run(*module);
    outputStream.flush();
}

vector<const char*> LogosLinker::getLinkerOpts() {
    return {
        DEFAULT_LINKER,
        objectFilePath,
        "-o", execFilePath,
        "-lSystem",
        "-syslibroot", LIB_ROOT,
        "-e", ENTRY_POINT,
        "-platform_version", OS_NAME, PLATFORM_VERSION, PLATFORM_VERSION,
        "-arch", ARCH_NAME,
    };
}


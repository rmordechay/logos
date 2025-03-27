#include "codegen/LgsLinker.h"

#include "CodeGenMetadata.h"

#include <CodeGenerator.h>
#include <LgsData.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FileSystem.h>

void LgsLinker::link(const std::map<std::string, Module*>& modules) const {
    const auto mainModule = modules.find(LOGOS_MAIN_FILE)->second;
    Linker linker(*mainModule);

    linkStdlib("../stdlib/lgslib.ll", &linker);
    linkStdlib("../stdlib/array.ll", &linker);
    for (const auto& [name, file] : modules) {
        if (name == LOGOS_MAIN_FILE) continue;
        linker.linkInModule(unique_ptr<Module>(std::move(file)));
    }

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
    auto stdlibModule = parseIRFile(path, EC, context);
    stdlibModule->setTargetTriple(targetTriple);
    stdlibModule->setDataLayout(targetMachine->createDataLayout());
    linker->linkInModule(unique_ptr(std::move(stdlibModule)));
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


#include "codegen/LgsLinker.h"
#include <CodeGenerator.h>
#include "LgsDefinitions.h"
#include <LogosMetadata.h>
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Object/ObjectFile.h>


namespace lld::macho {
    bool link(ArrayRef<const char *> argsArr, raw_ostream &stdoutOS, raw_ostream &stderrOS, bool exitEarly, bool disableOutput);
}

void LgsLinker::link(const std::map<std::string, Module*>& modules) {
    const auto lib = object::ObjectFile::createObjectFile(LOGOS_STDLIB);
    const auto mainModule = modules.find(LOGOS_MAIN_FILE)->second;
    Linker linker(*mainModule);
    linker.linkInModule(lib.get());
    for (const auto& [name, file] : modules) {
        if (name == LOGOS_MAIN_FILE) continue;
        linker.linkInModule(unique_ptr<Module>(std::move(file)));
    }

    writeExecFile(unique_ptr<Module>(mainModule));
    lld::macho::link(getLinkerOpts(), outs(), errs(), false, false);
}

void LgsLinker::writeExecFile(const unique_ptr<Module>& module) {
    error_code EC;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(objectFile.c_str(), EC, sys::fs::OF_None);
    targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    pass.run(*module);
    outputStream.flush();
}

vector<const char*> LgsLinker::getLinkerOpts() {
    return {
        DEFAULT_LINKER,
        objectFile.c_str(),
        "-o", execFile.c_str(),
        "-lSystem",
        "-syslibroot", LIB_ROOT,
        "-e", ENTRY_POINT,
        "-platform_version", OS_NAME, PLATFORM_VERSION, PLATFORM_VERSION,
        "-arch", ARCH_NAME,
    };
}


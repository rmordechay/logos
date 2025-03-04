#include "codegen/LogosLinker.h"

#include "CodeGenerator.h"
#include "LogosValue.h"
#include "LogosDefinitions.h"

#include <map>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include "llvm/Linker/Linker.h"

namespace lld::macho {
    bool link(ArrayRef<const char *> argsArr, raw_ostream &stdoutOS, raw_ostream &stderrOS, bool exitEarly, bool disableOutput);
}

void LogosLinker::link(const map<string, Module*>& modules) {
    auto stdlibModule = parseIRFile("../stdlib/logoslib.ll", EC, context);
    stdlibModule->setTargetTriple(targetTriple);
    stdlibModule->setDataLayout(targetMachine->createDataLayout());
    const auto mainModule = modules.find(LOGOS_MAIN_FILE)->second;
    Linker linker(*mainModule);
    linker.linkInModule(unique_ptr(std::move(stdlibModule)));
    for (const auto& [name, file] : modules) {
        if (name == LOGOS_MAIN_FILE) continue;
        linker.linkInModule(unique_ptr<Module>(std::move(file)));
    }

    writeFile(unique_ptr<Module>(mainModule), OBJECT_FILE_PATH);

    const auto args = {
        "ld.lld",
        OBJECT_FILE_PATH,
        "-o", EXECUTABLE_PATH,
        "-lSystem",
        "-syslibroot", "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk",
        "-e", "_main",
        "-platform_version", "macos", "14.0", "14.0",
        "-arch", "arm64"
    };
    lld::macho::link(args, outs(), errs(), false, false);
}

void LogosLinker::writeFile(const unique_ptr<Module> &module, const string &filename) {
    const string targetTriple = sys::getProcessTriple();
    string error;
    const Target *target = TargetRegistry::lookupTarget(targetTriple, error);

    const TargetOptions targetOptions;
    const unique_ptr<TargetMachine> targetMachine(
        target->createTargetMachine(targetTriple, sys::getHostCPUName(), "", targetOptions, Reloc::PIC_)
    );

    error_code EC;
    raw_fd_ostream outputStream(filename, EC, sys::fs::OF_None);

    legacy::PassManager pass;
    targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    pass.run(*module);
    outputStream.flush();
}


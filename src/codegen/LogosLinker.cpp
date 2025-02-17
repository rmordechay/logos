#include "codegen/LogosLinker.h"

#include "CodeGenerator.h"
#include "LogosValue.h"
#include "LogosDefinitions.h"

#include <map>
#include <llvm/Support/FileSystem.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/StringRef.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Object/ObjectFile.h>

void LogosLinker::link(const map<string, Module*>& modules) {
    auto mainModule = std::move(modules.find(LOGOS_MAIN_FILE)->second);
    auto logosLib = MemoryBuffer::getFile("../codegen/Print.ll");
    auto objectFile = object::ObjectFile::createObjectFile(logosLib->get()->getMemBufferRef());

    SMDiagnostic EC;
    auto printModule = parseIRFile("../codegen/Print.ll", EC, context);
    Linker::linkModules(*mainModule, unique_ptr(std::move(printModule)));

    for (auto module : modules) {
        if (module.first == LOGOS_MAIN_FILE) continue;
        Linker::linkModules(*mainModule, unique_ptr<Module>(std::move(module.second)));
    }
    writeFile(unique_ptr<Module>(std::move(mainModule)), "../linked.o");
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

void LogosLinker::runBinary() {
    system("cd ../stdlib && clang ../project/src/build/Main.ll ../project/src/build/MyObject.ll LogosStdlib.ll -o ../output");
    // system("ld -v -e main ../linked.o -o ../output");
    system("../output");
}

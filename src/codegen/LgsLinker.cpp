#include "codegen/LgsLinker.h"

#include "logos/Logos.h"
#include "logos/Platform.h"

#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/LegacyPassManager.h>

bool LgsLinker::link(LogosProject& project) const {
    setPlatform(paths.objFilePath, paths.execFilePath);
    Module* mainModule = project.IRModules.find(LOGOS_MAIN_FILE_NAME)->second;
    assert(mainModule);
    Linker linker(*mainModule);
    for (const auto& [name, module] : project.IRModules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        linker.linkInModule(unique_ptr<Module>(module));
    }
    if (!generateObjFile(mainModule, paths.objFilePath.c_str())) return false;
    const auto linkerOpts = platform.linkerOpts;
    if (!platform.link(linkerOpts, outs(), errs(), false, false)) {
        errs().flush();
        return false;
    }
    return true;
}

bool LgsLinker::generateObjFile(Module* module, const string& path) const {
    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(path, ec, sys::fs::OF_None);
    string error;
    const auto targetTriple = sys::getDefaultTargetTriple();
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    const auto targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
    const auto addedPassFailed = targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        cerr << ec.message() << endl;
        return false;
    }

    if (verifyModule(*module, &errs())) {
        errs().flush();
        return false;
    }

    pass.run(*module);
    outputStream.flush();
    outputStream.close();
    return true;
}

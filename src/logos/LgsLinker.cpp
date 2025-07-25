#include "logos/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include <llvm/Transforms/Utils/Cloning.h>

bool LgsLinker::link(const LgsPaths& paths, const map<string, LgsModule*>& modules) {
    const auto mainModule = modules.find(LOGOS_MAIN_FILE_NAME);
    assert(mainModule != modules.end());
    const auto mainCloned = CloneModule(*mainModule->second->IRModule);
    Linker llvmLinker(*mainCloned.get());
    for (const auto& [name, module] : modules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        llvmLinker.linkInModule(unique_ptr<Module>(module->IRModule));
    }

    if (!generateObjFile(paths, mainModule->second->IRModule)) {
        return false;
    }

    auto linkerOpts = platform.linkerOpts;
    linkerOpts.push_back(paths.objFilePath.c_str());
    linkerOpts.push_back("-o");
    linkerOpts.push_back(paths.execFilePath.c_str());
    if (!platform.link(linkerOpts, outs(), errs(), false, false)) {
        errs().flush();
        return false;
    }
    return true;
}

bool LgsLinker::generateObjFile(const LgsPaths& paths, Module* module) {
    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = getTargetMachine()->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
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

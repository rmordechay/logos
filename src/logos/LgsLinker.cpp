#include "logos/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

bool LgsLinker::link(const LgsPaths& paths, const map<string, Module*>& IRModules) const {
    Module* mainModule = IRModules.find(LOGOS_MAIN_FILE_NAME)->second;
    assert(mainModule);
    Linker llvmLinker(*mainModule);
    for (const auto& [name, module] : IRModules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        llvmLinker.linkInModule(unique_ptr<Module>(module));
    }
    if (!generateObjFile(paths, mainModule)) return false;
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

bool LgsLinker::generateObjFile(const LgsPaths& paths, Module* module) const {
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

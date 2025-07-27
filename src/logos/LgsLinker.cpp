#include "logos/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Transforms/Utils/Cloning.h>

bool validateModule(const Module* module) {
    string err;
    raw_string_ostream s(err);
    if (verifyModule(*module, &s)) {
        lgsLog(err, ERROR);
        return false;
    }
    return true;
}

bool generateObjFile(const LgsPaths& paths, Module* module) {
    // if (!validateModule(module)) return false;
    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = getTargetMachine()->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);

    if (addedPassFailed) {
        cerr << ec.message() << NEW_LINE;
        return false;
    }
    pass.run(*module);
    outputStream.flush();
    outputStream.close();
    return true;
}

bool link(const LgsPaths& paths) {
    LLVMContext context;
    unique_ptr<Module> mainModule = nullptr;
    vector<unique_ptr<Module>> modules;
    for (const auto& entry : directory_iterator(paths.buildIR)) {
        if (!isLLVMFile(entry)) continue;
        SMDiagnostic err;
        if (entry.path().filename().stem() == LOGOS_MAIN_FILE_NAME) {
            mainModule = parseIRFile(entry.path().string(), err, context);
        } else {
            auto module = parseIRFile(entry.path().string(), err, context);
            modules.push_back(std::move(module));
        }
    }
    Linker llvmLinker(*mainModule);
    for (auto& module : modules) {
        llvmLinker.linkInModule(std::move(module));
    }
    if (!generateObjFile(paths, mainModule.get())) {
        return false;
    }

    vector linkerOpts = LINKER_OPTS;
    linkerOpts.push_back(paths.objFilePath.c_str());
    linkerOpts.push_back("-o");
    linkerOpts.push_back(paths.execFilePath.c_str());
    if (!platform.link(linkerOpts, outs(), errs(), false, false)) {
        errs().flush();
        return false;
    }

    return true;
}

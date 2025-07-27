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
    for (const auto& entry : directory_iterator(paths.buildIR)) {
        if (!isLLVMFile(entry)) continue;
        if (entry.path().filename() == LOGOS_MAIN_FILE_NAME) {

        }
        SMDiagnostic err;
        // auto module = parseIRFile(entry.path().string(), err, context);
    }
    // Linker llvmLinker(*mainIRModule);
    // for (const auto [name, module] : modules) {
    //     if (name == LOGOS_MAIN_FILE_NAME) continue;
    //     llvmLinker.linkInModule(CloneModule(*module->IRModule));
    // }
    // if (!generateObjFile(paths, mainIRModule.get())) {
    //     return false;
    // }

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

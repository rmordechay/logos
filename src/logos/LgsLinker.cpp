#include "logos/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsIRUtils.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Transforms/Utils/Cloning.h>

bool generateObjFile(const LgsPaths& paths, Module* module) {
    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = getTargetMachine()->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        cerr << ec.message() << NEW_LINE;
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

unique_ptr<Module> cloneModuleToContext(const Module &src, LLVMContext &targetCtx) {
    string bitcodeStr;
    raw_string_ostream bitcodeStream(bitcodeStr);
    WriteBitcodeToFile(src, bitcodeStream);
    bitcodeStream.flush();
    const auto buffer = MemoryBuffer::getMemBufferCopy(bitcodeStr);
    auto modOrErr = parseBitcodeFile(buffer->getMemBufferRef(), targetCtx);
    if (!modOrErr) {
        logAllUnhandledErrors(modOrErr.takeError(), errs(), "Bitcode parse error: ");
        return nullptr;
    }
    return std::move(*modOrErr);
}

bool link(const LgsPaths& paths, const map<string, LgsModule*>& modules) {
    const auto mainModule = modules.find(LOGOS_MAIN_FILE_NAME);
    assert(mainModule != modules.end());
    const auto mainIRModule = mainModule->second->IRModule;
    const auto mainCloned = cloneModuleToContext(*mainIRModule, mainModule->second->context);
    Linker llvmLinker(*mainCloned);
    for (const auto& [name, module] : modules) {
        if (name == LOGOS_MAIN_FILE_NAME) continue;
        llvmLinker.linkInModule(cloneModuleToContext(*module->IRModule, mainModule->second->context));
    }
    if (!generateObjFile(paths, mainCloned.get())) {
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
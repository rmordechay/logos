#include "codegen/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsConfigs.h"
#include "utils/LgsUtils.h"
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Target/TargetMachine.h>

std::unique_ptr<Module> parseModule(LLVMContext& context, const std::string& path) {
    SMDiagnostic diag;
    auto parsedModule = parseIRFile(path, diag, context);
    if (!parsedModule) {
        std::stringstream errMsg;
        errMsg << diag.getMessage().str();
        errMsg << diag.getLineContents().str();
        for (auto fixIt : diag.getFixIts()) {
            errMsg << fixIt.getText().str();
        }
        logError(errMsg.str());
        return nullptr;
    }
    return parsedModule;
}

bool LgsLinker::link() {
    LLVMContext context;
    std::unique_ptr<Module> mainModule = nullptr;
    std::vector<std::unique_ptr<Module>> modules;
    const auto targetMachine = LgsLLVMGen::getTargetMachine();
    for (const auto& entry : fs::directory_iterator(paths.buildIR)) {
        if (!isLLVMFile(entry)) continue;
        auto module = parseModule(context, entry.path());
        if (!module) return false;
        if (entry.path().filename().stem() == LGS_MAIN_FILE_NAME) {
            mainModule = std::move(module);
        } else {
            modules.push_back(std::move(module));
        }
    }
    Linker llvmLinker(*mainModule);
    for (auto& module : modules) {
        llvmLinker.linkInModule(std::move(module));
    }
    if (!generateObjFile(std::move(mainModule), targetMachine)) {
        return false;
    }
    const auto lgsLibPath = findLgsLib();
    char linkCmd[1024];
    std::snprintf(
        linkCmd,
        sizeof(linkCmd),
        LINK_STRING,
        paths.objFilePath.c_str(),
        lgsLibPath.c_str(),
        lgsLibPath.c_str(),
        paths.execFilePath.c_str()
    );
    return std::system(linkCmd) == 0;
}

bool LgsLinker::generateObjFile(std::unique_ptr<Module> mainModule, TargetMachine* targetMachine) const {
    PassBuilder passBuilder(targetMachine);
    LoopAnalysisManager loopAnalyser;
    FunctionAnalysisManager funcAnalyser;
    CGSCCAnalysisManager CGAnalyser;
    ModuleAnalysisManager analysisManager;
    passBuilder.registerModuleAnalyses(analysisManager);
    passBuilder.registerFunctionAnalyses(funcAnalyser);
    passBuilder.registerLoopAnalyses(loopAnalyser);
    passBuilder.registerCGSCCAnalyses(CGAnalyser);
    passBuilder.crossRegisterProxies(loopAnalyser, funcAnalyser, CGAnalyser, analysisManager);

    PassManager<Module, AnalysisManager<Module>> passManager;
    const auto optLevel = getOptLevel(appConfigs.optLevel);
    passManager.addPass(std::move(passBuilder.buildPerModuleDefaultPipeline(optLevel)));
    passManager.run(*mainModule, analysisManager);

    std::error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        logError(ec.message() + '\n');
        return false;
    }

    pass.run(*mainModule);
    outputStream.flush();
    outputStream.close();
    return true;
}

std::string LgsLinker::findLgsLib() {
    if constexpr (IS_DEVELOPMENT) {
#ifdef __APPLE__
        return paths.rootPath.parent_path() / "cmake-build-debug";
#elif defined(__linux__)
        return paths.rootPath.parent_path() / "build";
#endif
    } else {
        return "$HOME/.logos/lib";
    }
}

OptimizationLevel LgsLinker::getOptLevel(const uint8_t level) const {
    if (appConfigs.optLevel == level) return OptimizationLevel::O0;
    if (appConfigs.optLevel == level) return OptimizationLevel::O1;
    if (appConfigs.optLevel == level) return OptimizationLevel::O2;
    if (appConfigs.optLevel == level) return OptimizationLevel::O3;
    assert(0);
}

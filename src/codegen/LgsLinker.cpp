#include "codegen/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"
#include "logos/LgsAppConfigs.h"
#include "utils/LgsUtils.h"
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Target/TargetMachine.h>

std::unique_ptr<Module> parseModule(LLVMContext& context, const std::string& path) {
    llvm::SMDiagnostic diag;
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

bool LgsLinker::link() const {
    LLVMContext context;
    std::unique_ptr<Module> mainModule = nullptr;
    std::vector<std::unique_ptr<Module>> modules;
    const auto targetMachine = LgsLLVMGen::getTargetMachine();
    std::vector<std::string> objectFiles;
    for (const auto& entry : fs::directory_iterator(paths.buildDirIR)) {
        if (!isLLVMFile(entry)) continue;
        auto module = parseModule(context, entry.path());
        if (!module) return false;
        auto objPath = paths.buildDirObjs / (entry.path().stem().string() + ".o");
        if (!generateObjFile(std::move(module), targetMachine, objPath)) {
            return false;
        }
        objectFiles.push_back(objPath.string());
    }
    const auto lgsLibPath = findLgsLib();
    std::string objFileList;
    for (const auto& objFile : objectFiles) {
        objFileList += objFile + " ";
    }
    char linkCmd[2048];
    std::snprintf(
        linkCmd,
        sizeof(linkCmd),
        LINK_STRING,
        objFileList.c_str(),
        lgsLibPath.c_str(),
        lgsLibPath.c_str(),
        paths.execFilePath.c_str()
    );
    return std::system(linkCmd) == 0;
}

bool LgsLinker::generateObjFile(std::unique_ptr<Module> module, TargetMachine* targetMachine, const std::string& outputPath) const {
    llvm::PassBuilder passBuilder(targetMachine);
    llvm::LoopAnalysisManager loopAnalyser;
    llvm::FunctionAnalysisManager funcAnalyser;
    llvm::CGSCCAnalysisManager CGAnalyser;
    llvm::ModuleAnalysisManager analysisManager;
    passBuilder.registerModuleAnalyses(analysisManager);
    passBuilder.registerFunctionAnalyses(funcAnalyser);
    passBuilder.registerLoopAnalyses(loopAnalyser);
    passBuilder.registerCGSCCAnalyses(CGAnalyser);
    passBuilder.crossRegisterProxies(loopAnalyser, funcAnalyser, CGAnalyser, analysisManager);
    llvm::PassManager<Module, llvm::AnalysisManager<Module>> passManager;
    const auto optLevel = getOptLevel(appConfigs.optLevel);
    passManager.addPass(passBuilder.buildPerModuleDefaultPipeline(optLevel));
    passManager.run(*module, analysisManager);

    std::error_code ec;
    llvm::legacy::PassManager pass;
    raw_fd_ostream outputStream(outputPath.c_str(), ec, llvm::sys::fs::OF_None);
    if (ec) {
        logError("Failed to open output file: " + ec.message() + '\n');
        return false;
    }

    const auto addedPassFailed = targetMachine->addPassesToEmitFile(
        pass, outputStream, nullptr, llvm::CodeGenFileType::ObjectFile
    );
    if (addedPassFailed) {
        logError("Failed to add passes to emit file\n");
        return false;
    }

    pass.run(*module);
    outputStream.flush();
    outputStream.close();
    return true;
}

std::string LgsLinker::findLgsLib() const {
#ifdef __APPLE__
        return paths.rootPath.parent_path() / "cmake-build-debug";
#elif defined(__linux__)
        return paths.rootPath.parent_path() / "build";
#endif
}

llvm::OptimizationLevel LgsLinker::getOptLevel(const uint8_t level) const {
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O0;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O1;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O2;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O3;
    assert(0);
}

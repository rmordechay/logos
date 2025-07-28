#include "logos/LgsLinker.h"
#include "data/LgsDefinitions.h"
#include "logos/LgsConfig.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/Transforms/Coroutines/CoroSplit.h>
#include <llvm/Transforms/Coroutines/CoroEarly.h>
#include <llvm/Transforms/Coroutines/CoroCleanup.h>
#include <llvm/Transforms/Coroutines/CoroElide.h>

unique_ptr<Module> parseModule(LLVMContext& context, const string& path) {
    SMDiagnostic diag;
    auto parsedModule = parseIRFile(path, diag, context);
    if (!parsedModule) {
        logErr(diag.getMessage().str());
        logErr(diag.getLineContents().str());
        for (auto fixIt : diag.getFixIts()) {
            logErr(fixIt.getText().str());
        }
        return nullptr;
    }
    return parsedModule;
}

bool LgsLinker::link() const {
    writeIRFiles();
    LLVMContext context;
    unique_ptr<Module> mainModule = nullptr;
    vector<unique_ptr<Module>> modules;
    for (const auto& entry : directory_iterator(paths.buildIR)) {
        if (!isLLVMFile(entry)) continue;
        auto module = parseModule(context, entry.path());
        if (!module) return false;
        if (entry.path().filename().stem() == LOGOS_MAIN_FILE_NAME) {
            mainModule = std::move(module);
        } else {
            modules.push_back(std::move(module));
        }
    }

    Linker llvmLinker(*mainModule);
    for (auto& module : modules) {
        llvmLinker.linkInModule(std::move(module));
    }

    if (!generateObjFile(std::move(mainModule))) return false;

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

bool LgsLinker::generateObjFile(unique_ptr<Module> mainModule) const {
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
    passManager.addPass(CoroEarlyPass());
    passManager.addPass(std::move(passBuilder.buildPerModuleDefaultPipeline(OptimizationLevel::O3)));
    passManager.addPass(createModuleToPostOrderCGSCCPassAdaptor(CoroSplitPass()));
    passManager.addPass(CoroCleanupPass());
    passManager.run(*mainModule, analysisManager);

    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = getTargetMachine()->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        logErr(ec.message() + NEW_LINE);
        return false;
    }

    pass.run(*mainModule);
    outputStream.flush();
    outputStream.close();
    return true;
}

void LgsLinker::writeIRFiles() const {
    for (const auto module : modules) {
        const auto IRModule = module.second->IRModule;
        if constexpr (WRITE_IR_TO_FILE) {
            const auto filePath = (paths.buildIR / IRModule->getName().str()).string() + ".ll";
            error_code EC;
            raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
            IRModule->print(textFile, nullptr);
        }
        if (logLevel == DEBUG) {
            IRModule->print(outs(), nullptr);
            logInfo("\n-----\n\n");
        }
    }
}



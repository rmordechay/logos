#include "logos/LgsLinker.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include "llvm/Linker/Linker.h"
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/Transforms/Coroutines/CoroSplit.h>
#include <llvm/Transforms/Coroutines/CoroEarly.h>
#include <llvm/Transforms/Coroutines/CoroCleanup.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IRReader/IRReader.h>

namespace lld::macho {
    bool link(ArrayRef<const char *> args, raw_ostream &stdoutOS, raw_ostream &stderrOS, bool exitEarly, bool disableOutput);
}

namespace lld::elf {
    bool link(ArrayRef<const char *> args, raw_ostream &stdoutOS, raw_ostream &stderrOS, bool exitEarly, bool disableOutput);
}

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

bool LgsLinker::link(TargetMachine* targetMachine) const {
    LLVMContext context;
    unique_ptr<Module> mainModule = nullptr;
    vector<unique_ptr<Module>> modules;
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
    const auto linkCmd = "clang++ -Lruntime -llgs_runtime " + paths.objFilePath.string() + " -o " + paths.execFilePath.string();
    std::system(linkCmd.c_str());
    return true;
}

bool LgsLinker::generateObjFile(unique_ptr<Module> mainModule, TargetMachine* targetMachine) const {
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
    passManager.addPass(createModuleToPostOrderCGSCCPassAdaptor(CoroSplitPass()));
    passManager.addPass(CoroCleanupPass());
    // passManager.addPass(std::move(passBuilder.buildPerModuleDefaultPipeline(OptimizationLevel::O3)));
    passManager.run(*mainModule, analysisManager);

    error_code ec;
    legacy::PassManager pass;
    raw_fd_ostream outputStream(paths.objFilePath.c_str(), ec, sys::fs::OF_None);
    const auto addedPassFailed = targetMachine->addPassesToEmitFile(pass, outputStream, nullptr, CodeGenFileType::ObjectFile);
    if (addedPassFailed) {
        logErr(ec.message() + '\n');
        return false;
    }

    pass.run(*mainModule);
    outputStream.flush();
    outputStream.close();
    return true;
}

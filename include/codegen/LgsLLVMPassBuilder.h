#pragma once
#include "LgsLLVMGen.h"
#include <llvm/Passes/PassBuilder.h>

class LgsLLVMPassBuilder {
public:
    llvm::PassBuilder builder;
    llvm::LoopAnalysisManager loopAnalyser;
    llvm::FunctionAnalysisManager funcAnalyser;
    llvm::CGSCCAnalysisManager CGAnalyser;
    llvm::ModuleAnalysisManager analysisManager;
    void init() {
        builder = llvm::PassBuilder(targetMachine);
        builder.registerModuleAnalyses(analysisManager);
        builder.registerFunctionAnalyses(funcAnalyser);
        builder.registerLoopAnalyses(loopAnalyser);
        builder.registerCGSCCAnalyses(CGAnalyser);
        builder.crossRegisterProxies(loopAnalyser, funcAnalyser, CGAnalyser, analysisManager);
    }
};

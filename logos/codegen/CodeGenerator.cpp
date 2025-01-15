#include "CodeGenerator.h"

#include "IfStmt.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include "llvm/Target/TargetMachine.h"
#include "llvm/Passes/PassBuilder.h"

void CodeGenerator::run(const vector<CodeNode*>& codeNodes) {
    RuntimeStackFrame rootFrame;
    const auto module = new Module("main", context);
    declareFunctions(module, &rootFrame);
    insertFunction(module, "main", builder.getInt32Ty(), &rootFrame);

    generate(codeNodes, rootFrame, module);

    builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0));
    std::error_code EC;
    const auto llvmFilePath = "../codegen/output.ll";
    raw_fd_ostream textFile(llvmFilePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
    compileLLVM(llvmFilePath, "../codegen/output");
    runBinary();
}

void CodeGenerator::generate(const vector<CodeNode*>& codeNodes, RuntimeStackFrame rootFrame, Module* const module) {
    for (const auto &codeNode : codeNodes) {
        codeNode->init(&context, &builder, module);
        codeNode->generateCode(&rootFrame);
    }
}

void CodeGenerator::declareFunctions(Module* module, RuntimeStackFrame* rootFrame) {
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::get(builder.getInt1Ty(), 0), true);
    rootFrame->functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
}

void CodeGenerator::insertFunction(Module* module, const string& name, IntegerType* rt, RuntimeStackFrame* frame) {
    const auto mainFuncType = FunctionType::get(rt, false);
    const auto mainFunc = Function::Create(mainFuncType, Function::ExternalLinkage, name, module);
    const auto mainEntry = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(mainEntry);
    frame->currentFunction = mainFunc;
}

void CodeGenerator::runBinary() {
    std::system("clang -o ../codegen/output ../codegen/output.o");
    std::system("../codegen/output");
}

void CodeGenerator::compileLLVM(const std::string& llvmFilePath, const std::string& outputFilePath) {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();

    const auto context = std::make_unique<LLVMContext>();
    const std::string errorMsg;
    auto buffer = MemoryBuffer::getFile(llvmFilePath, errorMsg.data());

    SMDiagnostic err;
    const auto module = parseIR(**buffer, err, *context);
    const auto targetTriple = sys::getProcessTriple();
    std::string targetError;
    const auto* target = TargetRegistry::lookupTarget(targetTriple, targetError);

    const auto options = TargetOptions();
    auto CPU = "generic";
    auto features = "";
    auto RM = Reloc::PIC_;
    auto targetMachine = target->createTargetMachine(targetTriple, CPU, features, options, RM);

    module->setDataLayout(targetMachine->createDataLayout());
    module->setTargetTriple(targetTriple);

    std::error_code EC;
    raw_fd_ostream dest(outputFilePath + ".o", EC, sys::fs::OF_None);
    if (EC) {
        errs() << "Error opening output file: " << EC.message() << "\n";
        return;
    }

    if (verifyModule(*module, &errs())) {
        errs() << "Module verification failed!\n";
        return;
    }

    auto emitPass = legacy::PassManager();
    auto fileType = CodeGenFileType::ObjectFile;
    targetMachine->addPassesToEmitFile(emitPass, dest, nullptr, fileType);
    emitPass.run(*module);
}

#include "CodeGenerator.h"

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
#include <llvm/Linker/Linker.h>

const auto PROGRAM_IR_FILE = "../codegen/output.ll";
const auto PRINT_IR_FILE = "../codegen/print.ll";
const auto LINKED_OBJECT_FILE = "../output.o";
const auto LINKED_IR_FILE = "../output.ll";
constexpr auto LLVM_OBJECT_FILE = CodeGenFileType::ObjectFile;

void CodeGenerator::run(const vector<CodeGeneration*>& codeNodes) {
    RuntimeStackFrame rootFrame;
    const auto module = new Module("main", context);
    declareFunctions(module, &rootFrame);
    insertFunction(module, "main", builder.getInt32Ty(), &rootFrame);

    generate(codeNodes, rootFrame, module);

    builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0));
    std::error_code EC;
    raw_fd_ostream textFile(PROGRAM_IR_FILE, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);

    initLLVM();
    initTargetMachine();
    linkModules();
    runBinary();
}

void CodeGenerator::generate(const vector<CodeGeneration*>& codeNodes, RuntimeStackFrame rootFrame, Module* const module) {
    for (const auto& codeNode : codeNodes) {
        codeNode->getLLVMValue(&builder, &rootFrame, module);
    }
}

void CodeGenerator::declareFunctions(Module* module, RuntimeStackFrame* rootFrame) {
    const auto printfType = FunctionType::get(builder.getVoidTy(), false);
    rootFrame->functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printInt", module);
}

void CodeGenerator::insertFunction(Module* module, const string& name, IntegerType* rt, RuntimeStackFrame* frame) {
    const auto mainFuncType = FunctionType::get(rt, false);
    const auto mainFunc = Function::Create(mainFuncType, Function::ExternalLinkage, name, module);
    const auto mainEntry = BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(mainEntry);
    frame->currentFunction = mainFunc;
}

void CodeGenerator::initTargetMachine() {
    std::string targetError;
    targetTriple = sys::getProcessTriple();
    target = TargetRegistry::lookupTarget(targetTriple, targetError);
    const auto TARGET_OPTIONS = TargetOptions();
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), Reloc::PIC_);
}

void CodeGenerator::linkModules() {
    const auto compositeModule = compileModule(PRINT_IR_FILE);
    Linker linker(*compositeModule);
    const auto inputFile = PROGRAM_IR_FILE;
    auto module = compileModule(inputFile);
    linker.linkInModule(std::move(module));
    if (verifyModule(*compositeModule, &errs())) return;
    std::error_code EC;
    raw_fd_ostream dest(LINKED_OBJECT_FILE, EC, sys::fs::OF_None);
    auto emitPass = legacy::PassManager();
    targetMachine->addPassesToEmitFile(emitPass, dest, nullptr, LLVM_OBJECT_FILE);
    emitPass.run(*compositeModule);
}

unique_ptr<Module> CodeGenerator::compileModule(const string& inputFile) {
    const std::string errorMsg;
    auto buffer = MemoryBuffer::getFile(inputFile, errorMsg.data());
    SMDiagnostic err;
    auto module = parseIR(**buffer, err, context);
    module->setDataLayout(targetMachine->createDataLayout());
    module->setTargetTriple(targetTriple);
    return module;
}

void CodeGenerator::initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
}

void CodeGenerator::runBinary() {
    std::system("clang ../output.o -o ../output");
    std::system("../output");
}

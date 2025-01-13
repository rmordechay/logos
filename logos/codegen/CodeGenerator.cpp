#include "CodeGenerator.h"

#include "StoreExpr.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/TargetSelect.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/CodeGen/CodeGenAction.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/MC/TargetRegistry.h>

void CodeGenerator::run(const std::vector<CodeNode*>& codeNodes) {
    const auto module = new Module("main", context);
    declareFunctions(module);
    insertMain(module);
    map<string, Value*> symbolTable;
    for (const auto node : codeNodes) {
        node->generateCode(builder, module, &functions, &symbolTable);
    }
    builder.CreateRetVoid();
    module->print(outs(), nullptr);
    writeToFile(module);
    runBinary();
    // compileLLVM("../codegen/output.ll", "../codegen/output");
}

void CodeGenerator::declareFunctions(Module* module) {
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::get(builder.getInt1Ty(), 0), true);
    functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
}

void CodeGenerator::insertMain(Module* module) {
    const auto voidType = Type::getVoidTy(context);
    const auto funcType = FunctionType::get(voidType, false);
    const auto mainFunction = Function::Create(funcType, Function::ExternalLinkage, "main", module);
    const auto entry = BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entry);
}

void CodeGenerator::addStoreExpr(const std::string& name, LogosExpr* expr) {
    codeNodes.push_back(new StoreExpr(name, expr));
}

void CodeGenerator::writeToFile(const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile("../codegen/output.ll", EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
}

void CodeGenerator::runBinary() {
    // std::system("llc -filetype=obj -mtriple=arm64-apple-macos ../codegen/output.ll -o ../codegen/output.o");
    std::system("clang -o ../codegen/output ../codegen/output.ll");
    std::system("../codegen/output");
}

void CodeGenerator::compileLLVM(const std::string& llvmFilePath, const std::string& outputFilePath) {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    clang::CompilerInstance compiler;
    compiler.createDiagnostics();

    const auto targetTriple = sys::getDefaultTargetTriple();
    compiler.getTargetOpts().Triple = targetTriple;
    compiler.getLangOpts().CPlusPlus = true;

    std::string error;
    auto target = TargetRegistry::lookupTarget(targetTriple, error);
    auto opt = TargetOptions{};
    auto RM = std::optional(Reloc::PIC_);
    auto CM = CodeModel::Small;

    auto machine = target->createTargetMachine(targetTriple, "apple-m2", "", opt, RM, CM);
    if (!machine) {
        throw std::runtime_error("Could not create target machine");
    }


    const clang::FrontendInputFile inputFile(llvmFilePath, clang::InputKind(clang::Language::LLVM_IR));
    compiler.getFrontendOpts().Inputs.push_back(inputFile);

    const auto codeGenAction = std::make_unique<clang::EmitLLVMAction>();
    if (!compiler.ExecuteAction(*codeGenAction)) {
        errs() << "Error generating LLVM IR.\n";
        return;
    }

    const auto module = codeGenAction->takeModule();
    if (!module) {
        errs() << "No module generated.\n";
        return;
    }

    std::error_code ec;
    raw_fd_ostream outputStream(outputFilePath, ec, sys::fs::OF_None);
    if (ec) {
        errs() << "Error opening output file: " << ec.message() << "\n";
        return;
    }

    module->print(outputStream, nullptr);
    outs() << "LLVM IR written to " << outputFilePath << "\n";
}


#include "CodeGenerator.h"

#include "LogosRootPackage.h"
#include "files/LogosObjectFile.h"

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

#include <iostream>
#include <llvm/Linker/Linker.h>

const auto PRINT_IR_FILE = "../codegen/print.ll";
const auto LINKED_OBJECT_FILE = "../output.o";
const auto LINKED_IR_FILE = "../output.ll";
constexpr auto LLVM_OBJECT_FILE = CodeGenFileType::ObjectFile;

void CodeGenerator::run(const LogosRootPackage* rootPackage) {
    initLLVM();
    for (const auto file : rootPackage->package->files) {
        if (const auto objFile = static_cast<LogosObjectFile*>(file)) {
            generateObjModule(objFile);
        }
    }

    const auto logosMainFile = rootPackage->mainFile;
    const auto mainModule = generateMainModule(logosMainFile);
    // linkModules(unique_ptr<Module>(mainModule));
    // runBinary();
    // generateTest();
}

Module* CodeGenerator::generateMainModule(const LogosMainFile* mainFile) {
    LLVMContext context;
    auto builder = IRBuilder(context);
    LogosStack theStack;
    theStack.push(LogosStackFrame());
    const auto module = createEmptyModule(LOGOS_MAIN_FILE, &builder);
    declareFunctions(module, &theStack, &builder);

    for (const auto func : mainFile->funcs) {
        func->getLLVMValue(&builder, &theStack, module);
    }

    mainFile->mainFunc->getLLVMValue(&builder, &theStack, module);
    builder.CreateRet(builder.getInt32(1));

    emitLLVMFile("../codegen/Main.ll", module);
    return module;
}

Module* CodeGenerator::generateObjModule(const LogosObjectFile* file) {
    LLVMContext context;
    auto builder = IRBuilder(context);

    LogosStack rootFrame;
    rootFrame.push(LogosStackFrame());

    const auto objName = file->name;
    const auto module = createEmptyModule(objName, &builder);

    vector<Type*> elementTypes;
    for (int i = 0; i < file->fields.size(); ++i) {
        const auto field = file->fields[i];
        auto fieldType = field->type->getLLVMType(&builder);
        elementTypes.push_back(fieldType);
        rootFrame.addSymbol(field->name, new LogosSymbol(fieldType, i));
    }

    const auto userStruct = StructType::create(context, elementTypes);
    rootFrame.addSymbol(LOGOS_THIS, new LogosSymbol(userStruct));

    for (const auto func : file->funcs) {
        func->getLLVMValue(&builder, &rootFrame, module);
    }

    emitLLVMFile("../codegen/" + objName + ".ll", module);
    return module;
}

Module* CodeGenerator::createEmptyModule(const string& name, const IRBuilder<>* builder) const {
    const auto module = new Module(name, builder->getContext());
    module->setDataLayout(targetMachine->createDataLayout());
    module->setTargetTriple(targetTriple);
    return module;
}

void CodeGenerator::emitLLVMFile(const string& filePath, const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
}

void CodeGenerator::linkModules(unique_ptr<Module> module) {
    LLVMContext context;
    const auto compositeModule = compileLLVMFile(PRINT_IR_FILE, &context);
    Linker linker(*compositeModule);
    linker.linkInModule(std::move(module));
    if (verifyModule(*compositeModule, &errs())) return;
    std::error_code EC;
    raw_fd_ostream dest(LINKED_OBJECT_FILE, EC, sys::fs::OF_None);
    auto emitPass = legacy::PassManager();
    targetMachine->addPassesToEmitFile(emitPass, dest, nullptr, LLVM_OBJECT_FILE);
    emitPass.run(*compositeModule);
}

void CodeGenerator::declareFunctions(Module* module, stack<LogosStackFrame>* rootFrame, IRBuilder<>* builder) {
    const auto printfType = FunctionType::get(builder->getVoidTy(), builder->getInt32Ty(), false);
    rootFrame->top().functions["print"] = Function::Create(printfType, Function::ExternalLinkage, "printInt", module);
}

unique_ptr<Module> CodeGenerator::compileLLVMFile(const string& inputFile, LLVMContext *context) {
    const std::string errorMsg;
    auto buffer = MemoryBuffer::getFile(inputFile, errorMsg.data());
    SMDiagnostic err;
    auto module = parseIR(**buffer, err, *context);
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

    std::string targetError;
    targetTriple = sys::getProcessTriple();
    target = TargetRegistry::lookupTarget(targetTriple, targetError);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), Reloc::PIC_);
}

void CodeGenerator::runBinary() {
    std::system("clang ../output.o -o ../output");
    std::system("../output");
}

void CodeGenerator::generateTest() {
    LLVMContext context;
    auto builder = IRBuilder(context);
    const std::vector<Type *> elements = {
        Type::getInt32Ty(context), Type::getFloatTy(context)
    };
    StructType *myStructType = StructType::create(context, elements, "MyStruct");
    AllocaInst *structInstance = builder.CreateAlloca(myStructType, nullptr, "myStructInstance");
    Value *fieldAPtr = builder.CreateStructGEP(myStructType, structInstance, 0, "a_ptr");

}

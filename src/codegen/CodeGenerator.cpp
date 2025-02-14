#include "CodeGenerator.h"

#include "funcs/LogosPrint.h"
#include "funcs/LogosUserFunc.h"


const auto LOGOS_LIB_IR_FILE = "../codegen/print.ll";
const auto LINKED_OBJECT_FILE = "../output.o";
const auto LINKED_IR_FILE = "../output.ll";
constexpr auto LLVM_OBJECT_FILE = CodeGenFileType::ObjectFile;

void CodeGenerator::run(const map<string, LogosFile*>& files, LogosStack& theStack) {
    theStack.addGlobalSymbol("print", LogosSymbol(FUNC, new LogosPrint()));

    auto builder = IRBuilder(context);
    const auto module = new Module(LOGOS_MAIN_FILE, context);
    const auto metadata = CodeGenMetadata{.builder = &builder, .theStack = &theStack, .module = module};
    const auto mainFile = dynamic_cast<LogosMainFile*>(files.at(LOGOS_MAIN_FILE));
    generateMainModule(mainFile, metadata, builder);
    runBinary();
}

void CodeGenerator::generateMainModule(const LogosMainFile* mainFile, CodeGenMetadata metadata, IRBuilder<>& builder) {
    mainFile->mainFunc->writeLLVMValue(&metadata);
    builder.CreateRet(builder.getInt32(EXIT_SUCCESS));
    for (const auto func : mainFile->funcs) {
        func->writeLLVMValue(&metadata);
    }
    writeIRToFile(metadata.module, LOGOS_MAIN_FILE);
}

void CodeGenerator::generateObjModule(LogosObject* obj, const LogosStack* theStack) {
    auto builder = IRBuilder(context);
    const auto module = new Module(obj->name(), context);
    auto logosStack = *theStack;
    while (logosStack.size() > 1) {
        logosStack.pop();
    }

    auto metadata = CodeGenMetadata{.builder = &builder, .theStack = &logosStack, .module = module};
    obj->writeLLVMType(&metadata);
    metadata.theStack->addGlobalSymbol("this", LogosSymbol(OBJECT, obj));
    for (const auto entry : obj->fields) {
        entry.second->writeLLVMValue(&metadata);
    }
    for (const auto entry : obj->funcs) {
        entry.second->writeLLVMValue(&metadata);
    }

    writeIRToFile(metadata.module, module->getName().str());
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
    std::system("cd ../codegen && clang Main.ll MyObject.ll Print.ll -o ../output");
    std::system("../output");
}

void CodeGenerator::generateTest() {
    LLVMContext context;
    auto builder = IRBuilder(context);
    const std::vector<Type*> elements = {Type::getInt32Ty(context), Type::getFloatTy(context),};
    StructType* myStructType = StructType::create(context, elements, "MyStruct");
    AllocaInst* structInstance = builder.CreateAlloca(myStructType, nullptr, "myStructInstance");
    Value* fieldAPtr = builder.CreateStructGEP(myStructType, structInstance, 0, "a_ptr");
}

void CodeGenerator::emitLLVMFile(const string& filePath, const Module* const module) {
    std::error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
    module->print(outs(), nullptr);
}

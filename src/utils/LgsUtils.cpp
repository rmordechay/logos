#include "utils/LgsUtils.h"
#include "LgsType.h"
#include "builtin/LgsBuiltins.h"

string getFileText(path filePath) {
    if (!exists(filePath)) return "";
    ifstream file(filePath);
    if (!file.is_open()) return "";
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

string removeUnderscores(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), '_'), result.end());
    return result;
}

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    // delete type;
}

void initLLVM() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    InitializeAllTargetMCs();
    InitializeAllTargets();
    InitializeAllTargetInfos();
}

Value* getIRStr(LgsModule* module, const string& value) {
    for (auto& globals : module->IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(module->context, value, true);
    const auto globalVariable = new GlobalVariable(*module->IRModule, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
    globalVariable->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    return globalVariable;
}

StructType* getIRStructType(LLVMContext& context, const string& name, const vector<Type*>& fields) {
    const auto structType = StructType::getTypeByName(context, name);
    if (!structType) {
        return StructType::create(context, fields, name);
    }
    return structType;
}

Module* createIRModule(const string& moduleName, LLVMContext& context) {
    const auto module = new Module(moduleName, context);
    module->setTargetTriple(sys::getDefaultTargetTriple());
    module->setDataLayout(getTargetMachine()->createDataLayout());
    return module;
}

GlobalVariable* createIRGlobal(const LgsModule* module, Type* type, Constant* value) {
    return new GlobalVariable(*module->IRModule, type, true, GlobalValue::PrivateLinkage, value);
}

void branchToBlock(LgsModule* module, BasicBlock* block) {
    if (!lastInstTerminator(module)) {
        module->builder.CreateBr(block);
    }
}

void startBlock(LgsModule* module, BasicBlock* block) {
    block->insertInto(module->stack.currentFunc->getIRFunc(module));
    module->builder.SetInsertPoint(block);
}

void startFuncBlock(LgsModule* module) {
    const auto currentFunc = module->stack.currentFunc;
    const auto IRFunc = currentFunc->getIRFunc(module);
    currentFunc->cleanupBlock = BasicBlock::Create(module->context, "cleanup");
    const auto entryBlock = BasicBlock::Create(module->context, "entry", IRFunc);
    module->builder.SetInsertPoint(entryBlock);
}

void copyMem(LgsModule* module, Value* src, Value* dest, const size_t n) {
    auto& builder = module->builder;
    builder.CreateCall(getMemcpy(module), {dest, src, i64(module, n), builder.getFalse()});
}

bool lastInstTerminator(const LgsModule* module) {
    return module->builder.GetInsertBlock()->getTerminator();
}

FunctionCallee getPrintf(LgsModule* module) {
    const auto funcType = FunctionType::get(i32Ty(module), {ptrTy(module)}, true);
    return module->IRModule->getOrInsertFunction("printf", funcType);
}

FunctionCallee getSnprintf(LgsModule* module) {
    const auto funcType = FunctionType::get(i32Ty(module), {ptrTy(module), i64Ty(module), ptrTy(module)}, true);
    return module->IRModule->getOrInsertFunction("snprintf", funcType);
}

FunctionCallee getStrHash(LgsModule* module) {
    const auto printfType = FunctionType::get(i32Ty(module), {ptrTy(module)}, false);
    return module->IRModule->getOrInsertFunction("Str_hash", printfType);
}

Function* getMemcpy(LgsModule* module) {
    const auto int64Ty = module->builder.getInt64Ty();
    const auto ptrTy = module->builder.getPtrTy();
    return getOrInsertDeclaration(module->IRModule, Intrinsic::memcpy, {ptrTy, ptrTy, int64Ty});
}

TargetMachine* getTargetMachine() {
    if (targetMachine) return targetMachine;
    const auto targetTriple = sys::getDefaultTargetTriple();
    string error;
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    lock_guard lock(mtx);
    targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), nullopt);
    return targetMachine;
}

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

size_t hashString(const string& str) {
    size_t hash = 2166136261u;
    for (const auto c : str) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    delete type;
}

Value* getIRStr(LgsModule* runtime, const string& value) {
    for (auto& globals : runtime->IRModule->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(runtime->context, value, true);
    const auto globalVariable = new GlobalVariable(*runtime->IRModule, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
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

bool hasTerminator(const LgsModule* runtime) {
    return runtime->builder.GetInsertBlock()->getTerminator();
}

PointerType* ptrTy(LLVMContext& context) {
    return PointerType::getUnqual(context);
}

Type* i1Ty(LLVMContext& context) {
    return IntegerType::getInt32Ty(context);
}

Type* i8Ty(LLVMContext& context) {
    return IntegerType::getInt32Ty(context);
}

Type* i16Ty(LLVMContext& context) {
    return IntegerType::getInt32Ty(context);
}

Type* i32Ty(LLVMContext& context) {
    return IntegerType::getInt32Ty(context);
}

Type* i64Ty(LLVMContext& context) {
    return IntegerType::getInt32Ty(context);
}

FunctionCallee getPrintf(LgsModule* runtime) {
    const auto funcType = FunctionType::get(i32Ty(runtime->context), {ptrTy(runtime->context)}, true);
    return runtime->IRModule->getOrInsertFunction("printf", funcType);
}

FunctionCallee getSnprintf(LgsModule* runtime) {
    const auto funcType = FunctionType::get(i32Ty(runtime->context), {ptrTy(runtime->context), runtime->builder.getInt64Ty(), ptrTy(runtime->context)}, true);
    return runtime->IRModule->getOrInsertFunction("snprintf", funcType);
}

FunctionCallee getStrHash(LgsModule* runtime) {
    const auto printfType = FunctionType::get(i32Ty(runtime->context), {ptrTy(runtime->context)}, false);
    return runtime->IRModule->getOrInsertFunction("Str_hash", printfType);
}

Function* getMemcpy(LgsModule* runtime) {
    const auto int64Ty = runtime->builder.getInt64Ty();
    const auto ptrTy = runtime->builder.getPtrTy();
    return getOrInsertDeclaration(runtime->IRModule, Intrinsic::memcpy, {ptrTy, ptrTy, int64Ty});
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

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
    dataLayout = getTargetMachine()->createDataLayout();
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

bool lastInstTerminator(const LgsModule* module) {
    return module->builder.GetInsertBlock()->getTerminator();
}

PointerType* ptrTy(LgsModule* module) {
    return PointerType::getUnqual(module->context);
}

Type* i1Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

Type* i8Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

Type* i16Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

Type* i32Ty(LgsModule* module) {
    return IntegerType::getInt32Ty(module->context);
}

Type* i64Ty(LgsModule* module) {
    return IntegerType::getInt64Ty(module->context);
}

Value* i1(LgsModule* module, const bool v) {
    return module->builder.getInt1(v);
}

Value* i8(LgsModule* module, const int8_t v) {
    return module->builder.getInt8(v);
}

Value* i16(LgsModule* module, const int16_t v) {
    return module->builder.getInt16(v);
}

Value* i32(LgsModule* module, const int32_t v) {
    return module->builder.getInt32(v);
}

Value* i64(LgsModule* module, const int64_t v) {
    return module->builder.getInt64(v);
}

FunctionCallee getPrintf(LgsModule* module) {
    const auto funcType = FunctionType::get(i32Ty(module), {ptrTy(module)}, true);
    return module->IRModule->getOrInsertFunction("printf", funcType);
}

FunctionCallee getSnprintf(LgsModule* module) {
    const auto funcType = FunctionType::get(i32Ty(module), {ptrTy(module), module->builder.getInt64Ty(), ptrTy(module)}, true);
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

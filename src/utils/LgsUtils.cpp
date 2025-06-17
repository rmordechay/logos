#include "utils/LgsUtils.h"
#include "logos/LgsApp.h"
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

Value* getIRStr(const LgsRuntime* runtime, const string& value) {
    for (auto& globals : runtime->module->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    const auto globalVariable = new GlobalVariable(*runtime->module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
    globalVariable->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    return globalVariable;
}

StructType* getIRStructType(const string& name, const vector<Type*>& fields) {
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

bool hasTerminator(const LgsRuntime* runtime) {
    return runtime->builder.GetInsertBlock()->getTerminator();
}

FunctionCallee getPrintf(LgsRuntime* runtime) {
    const auto printfType = FunctionType::get(runtime->builder.getInt32Ty(), {PointerType::getUnqual(context)}, true);
    return runtime->module->getOrInsertFunction("printf", printfType);
}

FunctionCallee getSnprintf(LgsRuntime* runtime) {
    const auto printfType = FunctionType::get(runtime->builder.getInt32Ty(), {PointerType::getUnqual(context), runtime->builder.getInt64Ty(), PointerType::getUnqual(context)}, true);
    return runtime->module->getOrInsertFunction("snprintf", printfType);
}

Function* getMemcpy(LgsRuntime* runtime) {
    const auto int64Ty = runtime->builder.getInt64Ty();
    const auto ptrTy = runtime->builder.getPtrTy();
    return getOrInsertDeclaration(runtime->module, Intrinsic::memcpy, {ptrTy, ptrTy, int64Ty});
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

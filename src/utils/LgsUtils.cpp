#include "utils/LgsUtils.h"
#include "exprs/unary/LgsVariable.h"
#include "logos/LgsApp.h"
#include "LgsType.h"

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

StructType* getIRStructType(LLVMContext& context, const string& name, const vector<Type*>& fields) {
    const auto struct_ = StructType::getTypeByName(context, name);
    if (!struct_) {
        return StructType::create(context, fields, name);
    }
    return struct_;
}

Module* createIRModule(const string& moduleName, LLVMContext& context) {
    const auto module = new Module(moduleName, context);
    module->setTargetTriple(sys::getDefaultTargetTriple());
    module->setDataLayout(getTargetMachine()->createDataLayout());
    return module;
}

FunctionCallee getPrintf(LgsRuntime* runtime) {
    const auto printfType = FunctionType::get(runtime->builder.getInt32Ty(), {PointerType::getUnqual(context)}, true);
    return runtime->module->getOrInsertFunction("printf", printfType);
}

FunctionCallee getSnprintf(LgsRuntime* runtime) {
    const auto printfType = FunctionType::get(runtime->builder.getInt32Ty(), {PointerType::getUnqual(context), runtime->builder.getInt64Ty(), PointerType::getUnqual(context)}, true);
    return runtime->module->getOrInsertFunction("snprintf", printfType);
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
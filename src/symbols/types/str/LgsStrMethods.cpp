#include "types/str/LgsStrMethods.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"

FunctionCallee getPrintf(Module* module) {
    const vector<Type*> printfArgsTypes = {ptrTy};
    FunctionType *printfType = FunctionType::get(Type::getInt32Ty(context), printfArgsTypes, true);
    return module->getOrInsertFunction("printf", printfType);
}

// int snprintf(char* restrict str, size_t size, const char* restrict format, ...);
FunctionCallee getSnprintf(Module* module) {
    const vector<Type*> printfArgsTypes = {ptrTy, i32Ty};
    FunctionType *printfType = FunctionType::get(Type::getInt32Ty(context), printfArgsTypes, true);
    return module->getOrInsertFunction("snprintf", printfType);
}

Value* LgsStrFormatFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    auto& builder = metadata->builder;
    auto baseStr = getBaseStr(args[0]);
    for (int i = 1; i < args.size(); ++i) {
        replaceNextPlaceholder(baseStr, args[i]);
    }

    const auto baseIRStr = getIRStr(metadata->module, baseStr);
    vector<Value*> IRArgs = {baseIRStr, builder.getInt32(baseStr.size())};
    for (int i = 1; i < args.size(); ++i) {
        IRArgs.emplace_back(args[i]->getIRValue(metadata));
    }
    const auto printfFunc = getSnprintf(metadata->module);
    return builder.CreateCall(printfFunc, IRArgs);
}

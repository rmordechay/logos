#include "types/str/LgsStrMethods.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include "exprs/LgsExpr.h"
#define BUFFER_SIZE 1024

FunctionCallee getPrintf(Module* module) {
    const vector<Type*> printfArgsTypes = {ptrTy};
    FunctionType* printfType = FunctionType::get(Type::getInt32Ty(context), printfArgsTypes, true);
    return module->getOrInsertFunction("printf", printfType);
}

FunctionCallee getSnprintf(Module* module) {
    const vector<Type*> printfArgsTypes = {ptrTy, i64Ty, ptrTy};
    FunctionType* printfType = FunctionType::get(Type::getInt32Ty(context), printfArgsTypes, true);
    return module->getOrInsertFunction("snprintf", printfType);
}

Value* LgsStrFormatFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    auto& builder = metadata->builder;
    const bool isConst = args[0]->type->isConst;
    if (!isConst) assert(false);
    const auto formatString = getFormatString(args);
    const auto baseIRStr = getIRStr(metadata->module, formatString);
    const auto bufferType = ArrayType::get(i8Ty, BUFFER_SIZE);
    const auto buffer = builder.CreateAlloca(bufferType);
    const auto gep = builder.CreateGEP(bufferType, buffer, {i32Zero, i32Zero});
    vector<Value*> IRArgs = {gep, builder.getInt64(BUFFER_SIZE), baseIRStr};
    for (int i = 1; i < args.size(); ++i) {
        IRArgs.emplace_back(args[i]->getIRValue(metadata));
    }
    const auto printfFunc = getSnprintf(metadata->module);
    builder.CreateCall(printfFunc, IRArgs);
    return gep;
}

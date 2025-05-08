#include "funcs/LgsMethodImpl.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsObject.h"

bool LgsMethodImpl::equals(const LgsFuncCall* other) {
    if (methodType.name != other->name) return false;
    const auto params = methodType.params;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    const auto argsSize = isStatic ? args.size() - 1 : args.size();
    if (params.size() < argsSize) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto paramType = params[i]->type;
        const auto argType = args[i + isStatic]->type;
        if (!paramType->equals(argType)) return false;
    }
    return true;
}

FunctionType* LgsMethodImpl::getIRFuncType(const CodeGenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
    // if (!isStatic) IRParamsTypes.emplace_back(ptrTy);
    for (int i = 0; i < methodType.params.size(); ++i) {
        auto paramIRType = methodType.params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    if (const auto obj = methodType.rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, false);
    } else {
        IRFuncType = FunctionType::get(methodType.rt->getIRType(), IRParamsTypes, false);
    }
    return IRFuncType;
}

void LgsMethodImpl::setIRParams(Function* func, Argument* args) {
    for (int i = 0; i < methodType.params.size(); ++i) {
        const auto param = methodType.params[i];
        param->setIRValue(args);
        if (param->expr) param->expr->setIRValue(args);
        auto paramName = param->name;
        if (paramName != "") args->setName(paramName);
        args++;
    }
}

LgsFuncType* LgsMethodImpl::getFuncType() {
    return &methodType;
}

#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

void LgsMethodImpl::setIRName() {
    vector<string> argTypeNames;
    for (const auto& param : signature.params) {
        argTypeNames.emplace_back(param.type->getName());
    }
    signature.IRName = signature.getComposedName(signature.name, parentName, argTypeNames);
}

void LgsMethodImpl::setIRFuncType(const CodeGenMetadata* metadata) {
    // TODO implement static
    vector<Type*> IRParamsTypes;
    IRParamsTypes.emplace_back(ptrTy);
    for (int i = 1; i < signature.params.size(); ++i) {
        auto paramIRType = signature.params[i].type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    if (const auto obj = signature.type->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, false);
    } else {
        IRFuncType = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    }
}

void LgsMethodImpl::setIRFuncParams(Argument* args) {
    for (int i = 0; i < signature.params.size(); ++i) {
        signature.params[i].setIRValue(args);
        if (signature.params[i].expr) signature.params[i].expr->setIRValue(args);
        args->setName(signature.params[i].name);
        args++;
    }
}

bool LgsMethodImpl::equals(const LgsFuncCall* other) {
    if (signature.name != other->name) return false;
    const auto params = signature.params;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    if (params.size() < args.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto paramType = params[i].type;
        const auto argType = args[i]->type;
        if (!paramType->equals(argType)) return false;
    }
    return true;
}

bool LgsMethodImpl::equals(const LgsFunc* other) {
    if (signature.name != other->signature.name) return false;
    const auto thisParams = signature.params;
    const auto otherParams = other->signature.params;
    if (thisParams.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < signature.params.size() - 1; ++i) {
        auto thisTypeName = signature.params[i + 1].type->getName();
        auto otherTypeName = other->signature.params[i].type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}
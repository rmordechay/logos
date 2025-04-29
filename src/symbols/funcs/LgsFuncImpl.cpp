#include "funcs/LgsFuncImpl.h"

#include "types/LgsObject.h"

void LgsFuncImpl::setIRFuncType(const CodeGenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
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

void LgsFuncImpl::setIRFuncParams(Argument* args) {
    for (auto& param : signature.params) {
        param.setIRValue(args);
        if (param.expr) param.expr->setIRValue(args);
        args->setName(param.name);
        args++;
    }
}

bool LgsFuncImpl::isEqual(const LgsFuncCall* funcCall) {
    if (!signature.isEqual(funcCall->name, funcCall->parentName, funcCall->type)) return false;
    if (signature.params.size() == 0) return true;
    for (size_t i = 0; i < signature.params.size(); ++i) {
        auto thisTypeName = signature.params[i].type->getName();
        auto otherTypeName = funcCall->args[i]->type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

bool LgsFuncImpl::isEqual(const LgsFuncSignature* other) {
    if (!signature.isEqual(other->name, other->parentName, other->type)) return false;
    if (signature.params.size() == 0) return true;
    for (size_t i = 0; i < signature.params.size() - 1; ++i) {
        auto thisTypeName = signature.params[i + 1].type->getName();
        auto otherTypeName = other->params[i].type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}
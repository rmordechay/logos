#include "funcs/LgsFuncImpl.h"

#include "types/LgsInterface.h"
#include "types/LgsObject.h"

void LgsFuncImpl::setIRName() {
    vector<string> argTypeNames;
    for (const auto& param : signature.params) {
        argTypeNames.emplace_back(param.type->getName());
    }
    signature.IRName = signature.getComposedName(signature.name, "", argTypeNames);
}

void LgsFuncImpl::setIRFuncType(const CodeGenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < signature.params.size(); ++i) {
        auto paramIRType = signature.params[i].type->getIRType();
        // TODO make generic
        if (dynamic_cast<LgsInterface*>(signature.params[i].type)) {
            paramIRType = paramIRType->getPointerTo();
        }
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

bool LgsFuncImpl::equals(const LgsFuncCall* other) {
    if (signature.name != other->name) return false;
    const auto params = signature.params;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    if (params.size() < args.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        assert(args[i]);
        auto thisTypeName = params[i].type->getName();
        auto otherTypeName = args[i]->type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

bool LgsFuncImpl::equals(const LgsFunc* other) {
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
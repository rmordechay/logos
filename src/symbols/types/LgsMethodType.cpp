#include "types/LgsMethodType.h"
#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"

string LgsMethodType::getIRName() {
    if (IRName != "") return IRName;
    vector<string> argTypeNames;
    for (const auto& param : params) {
        argTypeNames.emplace_back(param.type->getName());
    }
    IRName = getComposedName(name, parentName, argTypeNames);
    return IRName;
}

FunctionType* LgsMethodType::getIRFuncType(const CodeGenMetadata* metadata) {
    // TODO implement static
    vector<Type*> IRParamsTypes;
    IRParamsTypes.emplace_back(ptrTy);
    for (int i = 1; i < params.size(); ++i) {
        auto paramIRType = params[i].type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    if (const auto obj = type->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, false);
    } else {
        IRFuncType = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    }
    return IRFuncType;
}

void LgsMethodType::setIRFuncParams(Argument* args) {
    for (int i = 0; i < params.size(); ++i) {
        params[i].setIRValue(args);
        if (params[i].expr) params[i].expr->setIRValue(args);
        auto paramName = params[i].name;
        if (paramName != "") args->setName(paramName);
        args++;
    }
}

bool LgsMethodType::equals(LgsType* other) const {
    const auto otherFuncType = dynamic_cast<LgsFuncType*>(other);
    if (!otherFuncType) return false;
    if (name != otherFuncType->name) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < params.size() - 1; ++i) {
        auto thisTypeName = params[i + 1].type->getName();
        auto otherTypeName = otherFuncType->params[i].type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

string LgsFuncType::getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames) {
    stringstream strStream;
    if (parentName != "") {
        strStream << parentName << "_";
    }
    strStream << name;
    for (int i = 0; i < argTypeNames.size(); ++i) {
        strStream << "_" + argTypeNames[i];
    }
    return strStream.str();
}


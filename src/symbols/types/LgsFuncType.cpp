#include "types/LgsFuncType.h"

#include "logos/LgsConfig.h"
#include "types/LgsInterface.h"

bool LgsFuncType::equals(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    const auto otherParams = otherFuncType->params;
    if (!rt->equals(otherFuncType->rt)) return false;
    if (params.size() != otherParams.size()) return false;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto thisType = params[i]->type;
        const auto otherType = otherFuncType->params[i]->type;
        if (!thisType->equals(otherType)) return false;
    }
    return true;
}

string LgsFuncType::getIRName() {
    if (IRName != "") return IRName;
    stringstream strStream;
    if (isMethod) {
        strStream << parentName << "_";
    }
    strStream << name;
    IRName = strStream.str();
    return IRName;
}

Type* LgsFuncType::getIRType() {
    if (IRType) return IRType;
    Type* type;
    if (isRvBig && !swapReturn) {
        type = PointerType::getUnqual(context);
    } else {
        type = rt->getIRType();
    }
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param->type;
        auto paramIRType = paramType->getIRType();
        if (!paramType->isPrimitive) {
            paramIRType = PointerType::getUnqual(context);
        }
        IRParamsTypes.emplace_back(paramIRType);
    }
    IRType = FunctionType::get(type, IRParamsTypes, isVariadic);
    return IRType;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(false);
}

string LgsFuncType::prettyName() const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < params.size(); ++i) {
        strStream << params[i]->type->prettyName();
        if (i != params.size() - 1) strStream << ", ";
    }
    strStream << ')';
    return strStream.str();
}

LgsType* LgsFuncType::inferBinaryType(LgsType* other) {
    return nullptr;
}

LgsType* LgsFuncType::clone() {
    auto* newFuncType = new LgsFuncType();
    newFuncType->name = this->name;
    newFuncType->parentName = this->parentName;
    newFuncType->rt = this->rt->clone();
    for (const auto param : this->params) {
        newFuncType->params.push_back(new LgsParam(*param));
    }
    newFuncType->isMethod = this->isMethod;
    newFuncType->isStatic = this->isStatic;
    newFuncType->isPublic = this->isPublic;
    newFuncType->isVirtual = this->isVirtual;
    newFuncType->isVariadic = this->isVariadic;
    newFuncType->isAnonymous = this->isAnonymous;
    newFuncType->hasDefaultParams = this->hasDefaultParams;
    return newFuncType;
}

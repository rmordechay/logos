#include "types/LgsFuncType.h"
#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"

bool LgsFuncType::equals(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    const auto otherParams = otherFuncType->params;
    if (!rt->equals(otherFuncType->rt)) return false;
    if (params.size() != otherParams.size()) return false;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto thisType = params[i].type;
        const auto otherType = otherFuncType->params[i].type;
        if (!thisType->equals(otherType)) return false;
    }
    return true;
}

string LgsFuncType::getStrFormatPart() const {
    return "%p";
}

string LgsFuncType::getName() {
    if (IRName != "") return IRName;
    stringstream strStream;
    if (isMethod) {
        if (implementsName) {
            strStream << *implementsName << "_";
        } else {
            strStream << parentName << "_";
        }
    } else if (this->isAnonymous) {
        strStream << "Anonymous";
    }
    strStream << name;
    IRName = strStream.str();
    return IRName;
}

Type* LgsFuncType::getIRType(LgsModule* module) {
    if (IRType) return IRType;
    Type* returnType;
    if (isSizeBig && !isSwapReturn) {
        returnType = ptrTy(module);
    } else {
        returnType = rt->getIRType(module);
    }
    vector<Type*> IRParamsTypes;
    for (int i = isStaticMethod; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param.type;
        if (param.isSelf || !paramType->isPrimitive) {
            IRParamsTypes.emplace_back(ptrTy(module));
        } else {
            auto irType = paramType->getIRType(module);
            IRParamsTypes.emplace_back(irType);
        }
    }
    IRType = FunctionType::get(returnType, IRParamsTypes, this->isVariadic);
    return IRType;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

string LgsFuncType::prettyName() {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < params.size(); ++i) {
        strStream << params[i].type->prettyName();
        if (i != params.size() - 1) strStream << ", ";
    }
    if (rt) {
        strStream << "): " << rt->prettyName();
    } else {
        strStream << ')';
    }
    return strStream.str();
}

LgsFuncType::~LgsFuncType() {
    for (int i = isMethod && !isStaticMethod; i < params.size(); ++i) {
        const auto param = params[i];
        if (param.isSelf) continue;
        if (!param.expr) {
            freeType(param.type);
        } else {
            if (param.expr->type != param.type) {
                freeType(param.type);
            }
            delete param.expr;
        }
    }
}

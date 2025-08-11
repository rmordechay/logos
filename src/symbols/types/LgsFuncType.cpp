#include "types/LgsFuncType.h"
#include "configs/LgsConfig.h"
#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"

Type* LgsFuncType::getIRType(LgsCodeGen* codeGen) {
    vector<Type*> IRParamsTypes;
    for (int i = isStatic; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param.type;
        if (param.isSelf || !paramType->isPrimitive) {
            IRParamsTypes.emplace_back(codeGen->ptrTy());
        } else {
            IRParamsTypes.emplace_back(paramType->getIRType(codeGen));
        }
    }
    const auto isBigObject = rt->asObject() && rt->getSizeBytes() >= BIG_SIZE_THRESHOLD;
    if (isBigObject) {
        IRType = FunctionType::get(codeGen->ptrTy(), IRParamsTypes, this->isVariadic);
    } else {
        IRType = FunctionType::get(rt->getIRType(codeGen), IRParamsTypes, this->isVariadic);
    }
    return IRType;
}

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

string LgsFuncType::getName() {
    if (IRName != "") return IRName;
    stringstream strStream;
    if (isMethod) {
        if (parentName != "") {
            strStream << parentName << "_";
        }
    } else if (name == "") {
        strStream << "Anonymous";
    }
    strStream << name;
    IRName = strStream.str();
    return IRName;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

string LgsFuncType::prettyName() {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto param = params[i];
        strStream << param.type->prettyName();
        if (param.expr) {
            strStream << " = " << param.expr->prettyName();
        }
        if (i != params.size() - 1) strStream << ", ";
    }
    if (rt) {
        strStream << "): " << rt->prettyName();
    } else {
        strStream << ')';
    }
    return strStream.str();
}

string LgsFuncType::getStrFormatPart() const {
    return "%p";
}

size_t LgsFuncType::getSizeBytes() {
    return sizeof(void*);
}

LgsFuncType::~LgsFuncType() {
    for (int i = isMethod && !isStatic; i < params.size(); ++i) {
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

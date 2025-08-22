#include "types/LgsFuncType.h"
#include "configs/LgsConfig.h"
#include "configs/LgsDefinitions.h"
#include "logos/LgsCodeGen.h"
#include "utils/LgsUtils.h"

void LgsFuncType::setFuncOptions(const uint32_t ops) {
    isMethod = ops & METHOD;
    isPublic = ops & PUBLIC;
    isInternal = ops & INTERNAL;
    isVirtual = ops & VIRTUAL;
    isStatic = ops & STATIC;
    isVariadic = ops & VARIADIC;
    hasDefaults = ops & HAS_DEFAULTS;
    isOptional = ops & OPTIONAL;
    isTerminator = ops & TERMINATOR;
}

Type* LgsFuncType::getIRType(LgsCodeGen* codeGen) {
    std::vector<Type*> IRParamsTypes;
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
    const auto returnType = isBigObject ? codeGen->ptrTy() : rt->getIRType(codeGen);
    IRType = FunctionType::get(returnType, IRParamsTypes, this->isVariadic);
    return IRType;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

size_t LgsFuncType::getSizeBytes() {
    return sizeof(void*);
}

std::string LgsFuncType::getName() {
    if (IRName != "") return IRName;
    std::stringstream strStream;
    if (isMethod && !isVirtual) {
        strStream << parentName << "_";
    } else if (name == "") {
        strStream << LGS_ANONYMOUS_STR;
    }
    strStream << name;
    IRName = strStream.str();
    return IRName;
}

std::string LgsFuncType::pname() {
    std::stringstream strStream;
    if (isLambda) {
        strStream << LGS_ANONYMOUS_STR << '(';
    } else {
        strStream << name << '(';
    }
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto param = params[i];
        if (param.type) {
            strStream << param.type->pname();
        } else {
            strStream << param.name;
        }
        if (param.expr) {
            strStream << " = " << param.expr->pname();
        }
        if (i != params.size() - 1) strStream << ", ";
    }
    if (rt) {
        strStream << "): " << rt->pname();
    } else {
        strStream << ')';
    }
    return strStream.str();
}

json::value LgsFuncType::asJSON() {
    assert(0);
}

std::string LgsFuncType::strFormatPart() const {
    return "%p";
}

bool LgsFuncType::equals(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() != otherParams.size()) return false;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    if (otherFuncType->rt && !rt->equals(otherFuncType->rt)) return false;
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto thisType = params[i].type;
        const auto otherType = otherFuncType->params[i].type;
        if (!thisType->equals(otherType)) return false;
    }
    return true;
}

LgsType* LgsFuncType::clone() {
    const auto copy = new LgsFuncType();
    copy->name        = name;
    copy->IRName      = IRName;
    copy->parentName  = parentName;
    if (rt) copy->rt = rt->clone();
    copy->params.reserve(params.size());
    for (auto p : params) {
        copy->params.push_back(p.clone());
    }
    copy->isMethod    = isMethod;
    copy->isPublic    = isPublic;
    copy->isInternal  = isInternal;
    copy->isVirtual   = isVirtual;
    copy->isVariadic  = isVariadic;
    copy->isStatic    = isStatic;
    copy->isOptional  = isOptional;
    copy->isTerminator= isTerminator;
    copy->isLambda    = isLambda;
    copy->hasDefaults = hasDefaults;
    return copy;
}

LgsFuncType::~LgsFuncType() {
    freeType(rt);
    for (int i = isMethod && !isStatic; i < params.size(); ++i) {
        const auto param = params[i];
        if (param.isSelf) continue;
        if (param.expr) {
            if (param.type && param.expr->type != param.type) {
                freeType(param.type);
            }
            freeExpr(param.expr);
        } else if (param.type) {
            freeType(param.type);
        }
    }
    params.clear();
}

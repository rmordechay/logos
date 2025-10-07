#include "types/LgsFuncType.h"
#include "data/LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

void LgsFuncType::setFuncOptions(const uint32_t ops) {
    isPublic = ops & PUBLIC;
    isBuiltin = ops & BUILTIN;
    isVirtual = ops & VIRTUAL;
    isVariadic = ops & VARIADIC;
    isOptional = ops & OPTIONAL;
    isTerminator = ops & TERMINATOR;
    isMethod = ops & METHOD;
    isInIOPair = ops & IO;
    isSysCall = ops & SYSCALL;
}

Type* LgsFuncType::getIRType(LgsLLVMGen& cg) {
    std::vector<Type*> IRParamsTypes;
    for (int i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param.type;
        const auto isSelf = isMethod && i == 0;
        if (isSelf || !paramType->isPrimitive) {
            IRParamsTypes.emplace_back(cg.ptrTy());
        } else {
            IRParamsTypes.emplace_back(paramType->getIRType(cg));
        }
    }
    const auto returnType = rt->isBig() ? cg.ptrTy() : rt->getIRType(cg);
    IRType = cg.getFT(returnType, IRParamsTypes, this->isVariadic);
    return IRType;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

Lgs_rttype LgsFuncType::getRTType() {
    assert(0);
}

size_t LgsFuncType::getSizeBytes() {
    return sizeof(void*);
}

std::string LgsFuncType::getName() {
    if (IRName != "") return IRName;
    std::stringstream strStream;
    if (!isBuiltin) {
        strStream << "u_";
    }
    if (parentName != "") {
        strStream << parentName << "_";
    }
    strStream << name;
    IRName = strStream.str();
    return IRName;
}

std::string LgsFuncType::pname() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto param = params[i];
        if (param.type) {
            str << param.type->pname();
        } else if (param.name != ""){
            str << param.name;
        } else {
            str << LGS_UNKNOWN_TYPE;
        }
        if (param.expr) {
            str << " = " << param.expr->getName();
        }
        if (i != params.size() - 1) str << ", ";
    }
    if (rt) {
        str << "): " << rt->pname();
    } else {
        str << ')';
    }
    return str.str();
}

std::string LgsFuncType::strFormatPart() const {
    return "%p";
}

bool LgsFuncType::canCastTo(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() != otherParams.size()) return false;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    if (otherFuncType->rt && !rt->canCastTo(otherFuncType->rt)) return false;
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto thisType = params[i].type;
        const auto otherType = otherFuncType->params[i].type;
        if (!thisType || !otherType) return false;
        if (!thisType->canCastTo(otherType)) return false;
    }
    return true;
}

bool LgsFuncType::equals(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    if (name != otherFuncType->name) return false;
    if (!rt->equals(otherFuncType->rt)) return false;
    if (params.size() != otherFuncType->params.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param1 = params[i].type;
        const auto param2 = otherFuncType->params[i];
        if (!param1->equals(param2.type)) return false;
    }
    return true;
}

LgsType* LgsFuncType::clone() {
    const auto copy = new LgsFuncType();
    copy->name = name;
    copy->IRName = IRName;
    copy->parentName = parentName;
    if (rt) copy->rt = rt->clone();
    copy->params.reserve(params.size());
    for (auto p : params) {
        assert(0);
    }
    copy->isMethod = isMethod;
    copy->isPublic = isPublic;
    copy->isBuiltin = isBuiltin;
    copy->isVirtual = isVirtual;
    copy->isVariadic = isVariadic;
    copy->isOptional = isOptional;
    copy->isTerminator = isTerminator;
    copy->isInIOPair = isInIOPair;
    return copy;
}

bool LgsFuncType::hasDefaults() const {
    for (const auto& param : params) {
        if (param.expr) return true;
    }
    return false;
}

LgsFuncType::~LgsFuncType() {
    freeType(rt);
    if (isMethod) {
        params.erase(params.begin());
    }
    freeParams(params);
}

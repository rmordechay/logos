#include "types/LgsFuncType.h"
#include "data/LgsDefinitions.h"
#include "codegen/LgsLLVMGen.h"
#include "types/LgsGenericParam.h"
#include "utils/LgsUtils.h"
#include <sstream>

Type* LgsFuncType::getIRType(LgsLLVMGen& cg) {
    std::vector<Type*> types;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param.type;
        if (param.isVariadic) types.emplace_back(cg.sizeTy());
        if (param.type->passByRef) {
            types.emplace_back(cg.ptrTy());
        } else {
            types.emplace_back(paramType->getIRType(cg));
        }
    }
    const auto returnType = rt->isBig() ? cg.ptrTy() : rt->getIRType(cg);
    IRType = cg.getFT(returnType, types, this->isVariadic);
    return IRType;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

Lgs_TypeKind LgsFuncType::getRTTypeKind() {
    assert(0);
}

size_t LgsFuncType::sizeBytes() {
    return sizeof(void*);
}

std::string LgsFuncType::getName() {
    if (IRName != "") return IRName;
    std::stringstream strStream;
    if (!isExternal) {
        if (isBuiltin) strStream << LGS_NAME_PREFIX;
        else strStream << "u_";
    }
    if (parentName != "") strStream << parentName << "_";
    strStream << name;
    if (isCoroutine) strStream << LGS_CORO_SUFFIX;
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
            if (param.isVariadic) str << "...";
        } else if (param.name != ""){
            str << param.name;
        } else {
            str << LGS_UNKNOWN_TYPE;
        }
        if (param.expr) {
            str << " = " << param.expr->asText();
        }
        if (i != params.size() - 1) str << ", ";
    }
    if (rt) str << "): " << rt->pname();
    else str << ')';
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

void LgsFuncType::setFuncOptions(const uint32_t ops) {
    isPublic =  ops & PUBLIC;
    isBuiltin =  ops & BUILTIN;
    isVirtual =  ops & VIRTUAL;
    isVariadic =  ops & VARIADIC;
    isOptional =  ops & OPTIONAL;
    isTerminator =  ops & TERMINATOR;
    isMethod =  ops & METHOD;
    isCoroutine =  ops & COROUTINE;
    isIOMember =  ops & IO_MEMBER;
    isSyscall =  ops & SYSCALL;
    isExternal =  ops & EXTERNAL;
    isArrFunc =  ops & ARR_FUNC;
    hasDefaults =  ops & HAS_DEFAULTS;
}

LgsFuncType* LgsFuncType::clone() {
    const auto lgsFunc = new LgsFuncType();
    lgsFunc->name = name;
    lgsFunc->IRName = IRName;
    lgsFunc->parentName = parentName;
    lgsFunc->rt = rt ? rt->clone() : nullptr;
    for (const auto& param : params) {
        lgsFunc->params.push_back(LgsParam(param));
    }
    for (const auto generic : genericParams) {
        lgsFunc->genericParams.push_back(generic->clone());
    }
    lgsFunc->isPublic = isPublic;
    lgsFunc->isBuiltin = isBuiltin;
    lgsFunc->isVirtual = isVirtual;
    lgsFunc->isVariadic = isVariadic;
    lgsFunc->isLambda = isLambda;
    lgsFunc->isOptional = isOptional;
    lgsFunc->isTerminator = isTerminator;
    lgsFunc->isMethod = isMethod;
    lgsFunc->isSyscall = isSyscall;
    lgsFunc->isCoroutine = isCoroutine;
    lgsFunc->isIOMember = isIOMember;
    lgsFunc->isExternal = isExternal;
    lgsFunc->isArrFunc = isArrFunc;
    lgsFunc->hasDefaults = hasDefaults;
    lgsFunc->IRType = nullptr;
    return lgsFunc;
}

std::unordered_map<std::string, LgsParam*> LgsFuncType::getParamsByName() {
    std::unordered_map<std::string, LgsParam*> paramsByName;
    for (size_t i = 0; i < params.size(); ++i) {
        paramsByName[params[i].name] = &params[i];
    }
    return paramsByName;
}

LgsFuncType::~LgsFuncType() {
    freeType(rt);
    if (isMethod) {
        params.erase(params.begin());
    }
    freeParams(params);
}

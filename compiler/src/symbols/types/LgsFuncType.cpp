#include "types/LgsFuncType.h"
#include "LgsDefinitions.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsGenericType.h"
#include "LgsUtils.h"
#include <sstream>

Type* LgsFuncType::getIRType(LgsCgModule& cg) {
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
    const auto returnType = rt->passByRef ? cg.ptrTy() : rt->getIRType(cg);
    IRType = cg.getFT(returnType, types, this->isVariadic);
    return IRType;
}

Constant* LgsFuncType::getRTType(LgsCgModule& cg) {
    const auto funcName = getGenericName();
    std::vector<LgsOwner*> paramsAsOwners;
    for (auto& param : params) paramsAsOwners.emplace_back(static_cast<LgsOwner*>(&param));
    const auto [typesArr, hashesArr] = getRTFieldsInfo(cg, funcName, paramsAsOwners);
    // paramsCount, paramHashes, paramTypes, rt
    const auto sv = cg.getRTTExtraStruct(funcName, {cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, {
        cg.usize(params.size()), hashesArr, typesArr, rt->getRTType(cg)
    });
    return cg.getRTTypeInfo(funcName, sizeBytes(), RTT_FUNC, isHeapAlloc, sv);
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

size_t LgsFuncType::sizeBytes() {
    return sizeof(void*);
}

std::string LgsFuncType::getName() {
    if (name == "") return LGS_LAMBDA;
    std::stringstream strStream;
    if (!isExternal) {
        if (isBuiltin) strStream << LGS_PREFIX;
        else strStream << "u_";
    }
    if (parentName != "") {
        strStream << parentName << "_";
    }
    strStream << name;
    if (isCoroutine) strStream << LGS_CORO_SUFFIX;
    return strStream.str();
}

std::string LgsFuncType::getGenericName() {
    std::stringstream str;
    str << getName();
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto& param = params[i];
        str << '_' << param.type->getName();
    }
    return str.str();
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
            str << " = " << param.expr->asText();
        }
        if (i != params.size() - 1) str << ", ";
    }
    if (rt) str << "): " << rt->pname();
    else str << ')';
    return str.str();
}

std::string LgsFuncType::fmtStr() const {
    return "%p";
}

bool LgsFuncType::canCastTo(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() != otherParams.size()) return false;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    if (rt && otherFuncType->rt && !rt->canCastTo(otherFuncType->rt)) return false;
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

LgsType* LgsFuncType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
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
    hasDefaults =  ops & HAS_DEFAULTS;
}

std::unordered_map<std::string, LgsParam*> LgsFuncType::getParamsByName() {
    std::unordered_map<std::string, LgsParam*> paramsByName;
    for (size_t i = 0; i < params.size(); ++i) {
        paramsByName[params[i].name] = &params[i];
    }
    return paramsByName;
}

DIType* LgsFuncType::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsFuncType::~LgsFuncType() {
    if (!rt->asObject()) {
        if (!rt->asGenericType()) freeType(rt);
        rt = nullptr;
    }
    if (isMethod && !params.empty()) {
        params.erase(params.begin());
    }
    for (const auto& param : params) {
        if (param.isSelf) continue;
        if (param.expr) freeExpr(param.expr);
        freeType(param.type);
    }
    params.clear();
    for (const auto& genericType : genericTypes) {
        freeType(genericType);
    }
    genericTypes.clear();
}

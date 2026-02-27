#include "types/LgsFuncType.h"

#include <__ostream/basic_ostream.h>
#include <assert.h>
#include <ostream>
#include <sstream>

#include "LgsDefinitions.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsTypeParam.h"
#include "exprs/LgsExpr.h"

namespace llvm {
class Type;
}

FunctionType* LgsFuncType::getIRType(LgsCodeGen& cg) {
    assert(rt);
    std::vector<Type*> types;
    for (const auto& param : params) {
        if (param.isVariadic) {
            if (!isExternal) types.emplace_back(cg.sizeTy());
            break;
        }
        types.emplace_back(param.type->getStorageType(cg));
    }
    if (swapReturn) {
        types.insert(types.begin() + isMethod, cg.ptrTy());
        IRType = cg.getFT(cg.voidTy(), types, isVariadic);
    } else {
        IRType = cg.getFT(rt->getStorageType(cg), types, isVariadic);
    }
    return IRType;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

size_t LgsFuncType::sizeBytes() {
    return sizeof(void*);
}

std::string LgsFuncType::getName() {
    if (isExternal) return name;
    std::stringstream str;
    if (isBuiltin) str << LGS_PREFIX;
    else str << "u_";
    if (parentName != "") str << parentName << "_";
    str << name;
    for (size_t i = isMethod; i < params.size(); ++i) {
        str << '_' << (params[i].type ? params[i].type->getName() : LGS_UNKNOWN_TYPE);
    }
    if (isCoroutine) str << LGS_CORO_SUFFIX;
    return str.str();
}

std::string LgsFuncType::pname() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto param = params[i];
        str << (param.type ? param.type->pname() : LGS_UNKNOWN_TYPE);
        if (param.expr) str << " = " << param.expr->asText();
        if (i != params.size() - 1) str << ", ";
    }
    str << "): " << (rt ? rt->pname() : LGS_UNKNOWN_TYPE);
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
        if (!otherType) return false;
        if (!thisType) continue;
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
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto param1 = params[i].type;
        const auto param2 = otherFuncType->params[i];
        if (!param1->equals(param2.type)) return false;
    }
    return true;
}

bool LgsFuncType::hasTypeParams() {
    return !typeParams.empty();
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
    isSyscall =  ops & SYSCALL;
    isExternal =  ops & EXTERNAL;
    hasDefaults =  ops & HAS_DEFAULTS;
}

LgsType* LgsFuncType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

bool LgsFuncType::isRecursive(std::unordered_set<std::string>& visited) const {
    if (rt && rt->isRecursive(visited)) return true;
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto paramType = params[i].type;
        if (paramType && paramType->isRecursive(visited)) return true;
    }
    return false;
}

std::unordered_map<std::string, LgsParam*> LgsFuncType::getParamsByName() {
    std::unordered_map<std::string, LgsParam*> paramsByName;
    for (size_t i = 0; i < params.size(); ++i) {
        paramsByName[params[i].name] = &params[i];
    }
    return paramsByName;
}

DIType* LgsFuncType::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

void LgsFuncType::addSelf(LgsType* selfType) {
    isMethod = true;
    params.insert(params.begin(), LgsParam(selfType, LGS_SELF));
    params.front().isSelf = true;
}

LgsFuncType::~LgsFuncType() {
    if (isMethod && !params.empty()) {
        params.erase(params.begin());
    }
    for (const auto& param : params) {
        if (param.isSelf) continue;
        if (param.expr) freeExpr(param.expr);
    }
    params.clear();
    for (const auto& typeParam : typeParams) {
        freeType(typeParam);
    }
    typeParams.clear();
}

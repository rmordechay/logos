#include "types/LgsFuncType.h"

#include <__ostream/basic_ostream.h>
#include <assert.h>
#include <sstream>

#include "LgsDefinitions.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsGenericType.h"
#include "exprs/LgsExpr.h"

namespace llvm {
class Type;
}

FunctionType* LgsFuncType::getIRType(LgsCodeGen& cg) {
    assert(rt);
    std::vector<Type*> types;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param.type;
        if (param.isVariadic) types.emplace_back(cg.sizeTy());
        types.emplace_back(paramType->getStorageType(cg));
    }
    if (swapReturn) {
        types.insert(types.begin() + isMethod, cg.ptrTy());
        IRType = cg.getFT(cg.voidTy(), types, this->isVariadic);
    } else {
        IRType = cg.getFT(rt->getStorageType(cg), types, this->isVariadic);
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
    assert(name != "");
    if (isExternal) return name;
    std::stringstream str;
    if (isBuiltin) str << LGS_PREFIX;
    else str << "u_";
    if (parentName != "") str << parentName << "_";
    str << name;
    for (size_t i = isMethod; i < params.size(); ++i) {
        str << '_' << getTypeName(params[i].type);
    }
    if (isCoroutine) str << LGS_CORO_SUFFIX;
    return str.str();
}

std::string LgsFuncType::pname() {
    std::stringstream str;
    str << (isLambda ? "" : name) << '(';
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto param = params[i];
        str << getPrettyName(param.type);
        if (param.expr) str << " = " << param.expr->asText();
        if (i != params.size() - 1) str << ", ";
    }
    str << "): " << getPrettyName(rt);
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

bool LgsFuncType::hasGenerics() {
    if (rt && rt->hasGenerics()) return true;
    for (const auto& param : params) {
        if (param.type && param.type->hasGenerics()) return true;
    }
    return false;
}

void LgsFuncType::replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements) {
    const auto r = replacements.find(getName());
    if (r == replacements.end()) return;
    const auto replFuncType = r->second->asFuncType();
    for (size_t i = 0; i < params.size(); ++i) {
        auto paramName = params[i].type->getName();
        auto& repl = replacements[paramName];
        if (!replacements.contains(paramName)) continue;
        if (!repl) repl = replFuncType->params[i].type;
        assert(!repl->hasGenerics());
        params[i].type = repl;
    }
    auto& replacement = replacements[rt->getName()];
    if (!replacements.contains(rt->getName())) return;
    if (!replacement) replacement = replFuncType->rt;
    rt = replacement;
    genericTypes.clear();
}

LgsType* LgsFuncType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
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
    for (const auto& genericType : genericTypes) {
        freeType(genericType);
    }
    genericTypes.clear();
}

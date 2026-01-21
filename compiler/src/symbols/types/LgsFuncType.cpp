#include "types/LgsFuncType.h"
#include "LgsDefinitions.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsGenericType.h"
#include "LgsUtils.h"
#include <sstream>

Type* LgsFuncType::getIRType(LgsCgModule& cg) {
    assert(rt);
    std::vector<Type*> types;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        const auto paramType = param.type;
        if (param.isVariadic) types.emplace_back(cg.sizeTy());
        types.emplace_back(paramType->getTypeOrPtr(cg));
    }
    const auto returnType = rt->getTypeOrPtr(cg);
    IRType = cg.getFT(returnType, types, this->isVariadic);
    return IRType;
}

Constant* LgsFuncType::getRTType(LgsCgModule& cg) {
    const auto funcName = getName();
    std::vector<Constant*> paramNames;
    for (const auto& param : params) {
        paramNames.push_back(cg.getString(param.name));
    }

    const auto numFields = params.size();
    const auto RTTName = LGS_TYPEINFO_PREFIX + name;
    const auto namesArrType = ArrayType::get(cg.ptrTy(), numFields);
    const auto namesArr = cg.mode == CG_MODE_RTTYPES ? ConstantArray::get(namesArrType, paramNames) : nullptr;
    const auto namesArrGlobal = cg.createGlobal(RTTName + "_names", namesArrType, namesArr);

    // paramsCount, paramHashes, paramTypes, rt
    const std::vector<Type*> rttFieldTypes = {cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Constant*> args = {cg.usize(params.size()), namesArrGlobal, cg.null(), rt->getRTType(cg)};
    const auto sv = cg.getRTTExtraStruct(funcName, rttFieldTypes, args);
    return cg.getRTTypeInfo(funcName, IRSize(cg), RTT_FUNC, isHeapAlloc, sv);
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(0);
}

LgsType* LgsFuncType::replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) {
    const auto otherFT = replacement->asFuncType();
    if (!otherFT) return this;
    rt = rt->replaceGenerics(otherFT->rt, replacements);
    for (size_t i = 0; i < params.size(); ++i) {
        const auto otherParamType = otherFT->params[i].type;
        params[i].type = params[i].type->replaceGenerics(otherParamType, replacements);
    }
    return this;
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
    if (parentName != "") {
        str << parentName << "_";
    }
    str << name;
    for (size_t i = isMethod; i < params.size(); ++i) {
        const auto& param = params[i];
        str << '_' << param.type->getName();
    }
    if (isCoroutine) str << LGS_CORO_SUFFIX;
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
    for (size_t i = isMethod; i < params.size(); ++i) {
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

LgsFuncType* LgsFuncType::clone() {
    const auto newFuncType = new LgsFuncType(*this);
    newFuncType->rt = rt->clone();
    newFuncType->params.clear();
    for (const auto& param : params) {
        newFuncType->params.emplace_back(param.type->clone());
    }
    return newFuncType;
}

void LgsFuncType::addSelf(LgsType* selfType) {
    isMethod = true;
    params.insert(params.begin(), LgsParam(selfType, LGS_SELF));
    params.front().isSelf = true;
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

#include "exprs/LgsFuncCall.h"
#include "LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "LgsUtils.h"
#include "types/iterables/LgsVariadic.h"

#include <sstream>
bool argAndParamEqual(const LgsFuncArg* arg, const LgsParam* param);

Value* LgsFuncCall::loadIR(LgsCgModule& cg) {
    return IRValue;
}

bool LgsFuncCall::equals(LgsFuncType* funcType) const {
    if (args.empty() && funcType->params.empty()) return true;
    if (funcType->isVariadic) return equalsVariadic(funcType);
    if (funcType->hasDefaults) return equalsDefaults(funcType);

    const auto argsSize = args.size();
    const auto paramsSize = funcType->params.size();
    if (argsSize != paramsSize) return false;
    if (isNamed) {
        auto paramsByName = funcType->getParamsByName();
        for (size_t i = funcType->isMethod; i < argsSize; ++i) {
            const auto arg = args[i];
            const auto param = paramsByName[arg.name];
            if (argAndParamEqual(&arg, param)) continue;
            return false;
        }
    } else {
        for (size_t i = funcType->isMethod; i < paramsSize; ++i) {
            if (i >= argsSize) continue;
            const auto arg = args[i];
            const auto param = funcType->params[i];
            if (argAndParamEqual(&arg, &param)) continue;
            return false;
        }
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    const auto paramsSize = funcType->params.size();
    const auto minArgs = funcType->isExternal ? paramsSize - 1 : paramsSize;
    if (argsSize < minArgs) return false;
    // Check all args until the variadic param
    for (size_t i = funcType->isMethod; i < paramsSize - 1; ++i) {
        if (i >= args.size()) continue;
        const auto arg = args[i];
        const auto param = funcType->params[i];
        if (!argAndParamEqual(&arg, &param)) return false;
    }
    // Check the variadic arguments
    const auto& variadicParam = funcType->params.back();
    const auto variadic = variadicParam.type->asVariadic();
    assert(variadic);
    for (uint32_t i = variadicParam.index; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!arg.expr->type->canCastTo(variadic->baseType)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsDefaults(LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    const auto paramsSize = funcType->params.size();
    if (isNamed) {
        auto paramsByName = funcType->getParamsByName();
        for (size_t i = funcType->isMethod; i < argsSize; ++i) {
            const auto arg = args[i];
            const auto param = paramsByName[arg.name];
            if (argAndParamEqual(&arg, param)) continue;
            return false;
        }
    } else {
        for (size_t i = funcType->isMethod; i < paramsSize; ++i) {
            if (i >= argsSize) continue;
            const auto arg = args[i];
            const auto param = funcType->params[i];
            if (argAndParamEqual(&arg, &param)) continue;
            return false;
        }
    }
    return true;
}

bool LgsFuncCall::equals(LgsExpr* other) {
    const auto otherFuncCall = other->asFuncCall();
    if (!otherFuncCall || !otherFuncCall->func) return false;
    return equals(otherFuncCall->func->funcType);
}

std::string LgsFuncCall::getGenericName() const {
    std::stringstream str;
    str << "u_" << name;
    for (size_t i = inSelection; i < args.size(); ++i) {
        const auto arg = args[i];
        str << '_' << arg.expr->type->getName();
    }
    return str.str();
}

Value* LgsFuncCall::castIR(LgsCgModule& cg, LgsType* toType) {
    if (type->getName() == toType->getName()) return IRValue;
    assert(0);
}

std::string LgsFuncCall::asText() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
        const auto arg = args[i];
        if (arg.isSelf) continue;
        str << (arg.expr->type ? arg.expr->type->pname() : LGS_UNKNOWN_TYPE);
        if (i == args.size() - 1) continue;
        str << ", ";
    }
    if (type && !type->isUnknown()) {
        str << "): " << type->pname();
    } else {
        str << ')';
    }
    return str.str();
}

void LgsFuncCall::setDebugValue(LgsCgModule& cg) {
    cg.builder.SetCurrentDebugLocation(cg.getDebugLoc(location));
}

bool argAndParamEqual(const LgsFuncArg* arg, const LgsParam* param) {
    return arg->expr->type && arg->expr->type->canCastTo(param->type);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        if (arg.isSelf) continue;
        freeExpr(arg.expr);
    }
}
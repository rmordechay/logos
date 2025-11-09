#include "exprs/LgsFuncCall.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsVariable.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "utils/LgsUtils.h"

#include <iostream>
#include <sstream>

Value* LgsFuncCall::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

bool LgsFuncCall::equals(const LgsFuncType* funcType) const {
    if (funcType->isVariadic) return equalsVariadic(funcType);
    if (args.size() - funcType->isMethod > funcType->params.size()) return false;
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        if (i >= args.size()) continue;
        const auto arg = args[i];
        const auto param = funcType->params[i];
        if (!arg->type || !arg->type->canCastTo(param.type)) {
            return false;
        }
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    if (args.size() - funcType->isMethod <= funcType->params.size()) return false;
    // Check all args until the variadic param
    for (size_t i = funcType->isMethod; i < funcType->params.size() - 1; ++i) {
        if (i >= args.size()) continue;
        const auto arg = args[i];
        const auto param = funcType->params[i];
        if (!arg->type || !arg->type->canCastTo(param.type)) {
            return false;
        }
    }
    // Check the variadic arguments
    const auto& variadicParam = funcType->params.back();
    for (uint32_t i = variadicParam.index; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!arg->type || !arg->type->canCastTo(variadicParam.type)) {
            return false;
        }
    }
    return true;
}

bool LgsFuncCall::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsFuncCall::getGenericName() const {
    std::stringstream str;
    str << "u_" << name;
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        const auto arg = args[i];
        str << '_' << arg->type->getName();
    }
    return str.str();
}

Value* LgsFuncCall::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    if (type->getName() == toType->getName()) return IRValue;
    assert(0);
}

std::string LgsFuncCall::asText() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
        const auto arg = args[i];
        str << (arg->type ? arg->type->pname() : LGS_UNKNOWN_TYPE);
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

void LgsFuncCall::setDebugValue(LgsLLVMGen& cg) {
    cg.builder.SetCurrentDebugLocation(getDebugLoc(cg));
}

LgsStmt* LgsFuncCall::cloneStmt() {
    const auto newFuncCall = new LgsFuncCall(*this);
    newFuncCall->args.clear();
    for (const auto arg : args) {
        newFuncCall->args.emplace_back(arg->cloneExpr());
    }
    if (type) newFuncCall->type = type->clone();
    return newFuncCall;
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        freeExpr(arg);
    }
}

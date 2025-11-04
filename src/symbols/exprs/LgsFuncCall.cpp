#include "exprs/LgsFuncCall.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsVariable.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "utils/LgsUtils.h"
#include <sstream>

Value* LgsFuncCall::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

bool LgsFuncCall::equals(LgsExpr* other) {
    const auto otherFuncCall = other->asFuncCall();
    if (!otherFuncCall) return false;
    return name == otherFuncCall->name;
}

bool LgsFuncCall::equals(const LgsFuncType* other) const {
    if (other->isVariadic) return equalsVariadic(other);
    if (args.size() - other->isMethod > other->params.size()) return false;
    for (size_t i = other->isMethod; i < other->params.size(); ++i) {
        if (i >= args.size()) continue;
        const auto arg = args[i];
        const auto param = other->params[i];
        if (!arg->type || !arg->type->canCastTo(param.type)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
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

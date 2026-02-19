#include "exprs/LgsFuncCall.h"
#include "LgsDefinitions.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "LgsUtils.h"
#include "types/iterables/LgsVariadic.h"
#include <sstream>

bool argAndParamEqual(const LgsExpr* arg, const LgsParam* param);

bool LgsFuncCall::equals(LgsFuncType* funcType) const {
    // Compare args and params size
    const auto argsSize = args.size();
    const auto paramsSize = funcType->params.size();
    size_t minArgs = 0;
    if (funcType->isVariadic) {
        minArgs = paramsSize - 1;
    } else if (funcType->hasDefaults) {
        for (minArgs = 0; minArgs < paramsSize; ++minArgs) {
            if (funcType->params[minArgs].expr) break;
        }
    } else {
        minArgs = paramsSize;
    }
    if (argsSize < minArgs) return false;

    // Names params
    if (isNamed) {
        auto paramsByName = funcType->getParamsByName();
        for (size_t i = funcType->isMethod; i < argsSize; ++i) {
            if (!argAndParamEqual(args[i].expr, paramsByName[args[i].name])) return false;
        }
        return true;
    }

    // Positional params
    const auto checkUntil = funcType->isVariadic ? paramsSize - 1 : paramsSize;
    for (size_t i = funcType->isMethod; i < checkUntil; ++i) {
        if (i >= argsSize) continue;
        if (!argAndParamEqual(args[i].expr, &funcType->params[i])) return false;
    }

    // Remaining variadic args
    if (funcType->isVariadic && !funcType->isExternal) {
        const auto variadic = funcType->params.back().type->asVariadic();
        assert(variadic);
        for (size_t i = paramsSize; i < argsSize; ++i) {
            if (!args[i].expr->type->canCastTo(variadic->baseType)) return false;
        }
    }
    return true;
}

bool LgsFuncCall::equals(LgsExpr* other) {
    const auto otherFuncCall = other->asFuncCall();
    if (!otherFuncCall || !otherFuncCall->func) return false;
    return equals(otherFuncCall->func->funcType);
}

std::string LgsFuncCall::mangleName() const {
    std::stringstream str;
    str << "u_" << name;
    for (size_t i = inSelection; i < args.size(); ++i) {
        const auto arg = args[i];
        str << '_' << arg.expr->type->getName();
    }
    return str.str();
}

std::string LgsFuncCall::asText() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
        const auto arg = args[i];
        if (arg.isSelf) continue;
        str << arg.expr->asText();
        if (i == args.size() - 1) continue;
        str << ", ";
    }
    if (!type || type->isUnknown()) str << ')';
    else  str << "): " << type->pname();
    return str.str();
}

void LgsFuncCall::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
}

LgsFuncCall* LgsFuncCall::clone() {
    const auto newFuncCall = new LgsFuncCall(*this);
    newFuncCall->args.clear();
    for (const auto& arg : args) {
        newFuncCall->args.emplace_back(arg.expr->clone(), arg.name, arg.isSelf);
    }
    newFuncCall->setType(type);
    return newFuncCall;
}

bool argAndParamEqual(const LgsExpr* arg, const LgsParam* param) {
    if (!param->type || !arg->type) return false;
    return arg->type->canCastTo(param->type);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        if (arg.isSelf) continue;
        freeExpr(arg.expr);
    }
}
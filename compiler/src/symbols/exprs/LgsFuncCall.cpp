#include "exprs/LgsFuncCall.h"

#include <__ostream/basic_ostream.h>
#include <sstream>
#include <unordered_map>

#include "funcs/LgsFunc.h"
#include "LgsType.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsFuncType.h"
#include "types/iterables/LgsVariadic.h"

bool argAndParamEqual(LgsType* arg, LgsType* param);

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
            if (!argAndParamEqual(args[i].expr->type, paramsByName[args[i].name]->type)) return false;
        }
        return true;
    }

    // Positional params
    const auto checkUntil = funcType->isVariadic ? paramsSize - 1 : paramsSize;
    for (size_t i = funcType->isMethod; i < checkUntil; ++i) {
        if (i >= argsSize) continue;
        if (!argAndParamEqual(args[i].expr->type, funcType->params[i].type)) return false;
    }

    // Remaining variadic args
    if (funcType->isVariadic && !funcType->isExternal) {
        const auto variadicParam = funcType->params.back().type->asVariadic();
        for (size_t i = paramsSize; i < argsSize; ++i) {
            if (!argAndParamEqual(args[i].expr->type, variadicParam->baseType)) return false;
        }
    }
    return true;
}

std::string LgsFuncCall::asText() {
    std::stringstream str;
    str << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
        const auto arg = args[i];
        if (arg.name == LGS_SELF) continue;
        str << arg.expr->asText();
        if (i == args.size() - 1) continue;
        str << ", ";
    }
    if (!type || type->isUnknown()) str << ')';
    else  str << "): " << type->pname();
    return str.str();
}

std::string LgsFuncCall::mangleName() const {
    std::stringstream str;
    str << "u_" << name;
    for (size_t i = 0; i < args.size(); ++i) {
        const auto arg = args[i];
        str << '_' << arg.expr->type->getName();
    }
    return str.str();
}

void LgsFuncCall::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
}

LgsFuncCall* LgsFuncCall::clone() const {
    const auto newFuncCall = new LgsFuncCall(*this);
    newFuncCall->args.clear();
    for (const auto& arg : args) {
        newFuncCall->args.emplace_back(arg.name, arg.expr->clone());
    }
    newFuncCall->setType(type);
    return newFuncCall;
}

bool argAndParamEqual(LgsType* arg, LgsType* param) {
    if (!param || !arg) return false;
    return arg->canCastTo(param);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        if (arg.name == LGS_SELF) continue;
        freeExpr(arg.expr);
    }
}

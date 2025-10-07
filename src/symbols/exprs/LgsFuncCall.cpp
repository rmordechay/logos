#include "exprs/LgsFuncCall.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsHashMap.h"
#include "exprs/LgsVariable.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

Value* LgsFuncCall::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

bool LgsFuncCall::equals(LgsExpr* other) {
    const auto otherFuncCall = other->asFuncCall();
    if (!otherFuncCall) return false;
    return name == otherFuncCall->name;
}

bool LgsFuncCall::equals(const LgsFuncType* other) const {
    if (other->hasDefaults()) return equalsDefaultParams(other);
    if (other->isVariadic) return equalsVariadic(other);
    for (size_t i = 0; i < other->params.size(); ++i) {
        if (i >= args.size()) break;
        const auto arg = args[i];
        const auto param = other->params[i];
        const auto argType = arg->type;
        const auto paramType = param.type;
        if (!paramType || !argType) return false;
        if (arg->asNullableExpr() && !paramType->asNullable()) return false;
        if (!argType->canCastTo(paramType)) return false;
    }
    return true;
}

bool LgsFuncCall::equalsVariadic(const LgsFuncType* funcType) const {
    return true;
}

bool LgsFuncCall::equalsDefaultParams(const LgsFuncType* funcType) const {
    const auto argsSize = args.size();
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        const auto param = funcType->params[i];
        if (i >= argsSize) continue;
        const auto arg = args[i];
        if (!param.type->canCastTo(arg->type)) return false;
    }
    return true;
}

std::string LgsFuncCall::getName() {
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

void LgsFuncCall::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);

    addJsonKeyValue(json, "kind", "FuncCall", true);
    addJsonKeyValue(json, "name", name, true);

    openJsonKey(json, "args");
    openJsonArray(json);
    bool first = true;
    for (const auto arg : args) {
        if (!first) json << ',';
        first = false;
        arg->parseAsJSON(json);
    }
    closeJsonArray(json);

    closeJsonObject(json);
}

LgsFuncCall::~LgsFuncCall() {
    for (const auto& arg : args) {
        delete arg;
    }
}

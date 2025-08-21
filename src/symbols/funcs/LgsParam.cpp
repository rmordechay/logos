#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

void LgsParam::createIRValue(LgsCodeGen* codeGen) {
    if (isVariadic) {
        if (vaList) {
            IRValue = vaList;
            return;
        }
        vaList = codeGen->builder.CreateAlloca(codeGen->builder.getPtrTy());
        const auto vaStart = Intrinsic::getDeclaration(codeGen->IRModule, Intrinsic::vastart, {codeGen->builder.getPtrTy()});
        codeGen->builder.CreateCall(vaStart, {vaList});
        IRValue = vaList;
    }
}

json::value LgsParam::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}

LgsParam LgsParam::clone() const {
    LgsParam newParam(type->clone(), name);
    newParam.expr = expr ? expr->clone() : nullptr;
    newParam.isVariadic = isVariadic;
    newParam.isSelf = isSelf;
    return newParam;
}

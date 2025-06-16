#include "funcs/LgsParam.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->pName();
}

Value* LgsParam::getIRValue(LgsRuntime* runtime) {
    if (IRValue) return IRValue;
    if (isVariadic) {
        if (vaList) return vaList;
        vaList = runtime->builder.CreateAlloca(runtime->builder.getPtrTy());
        const auto vaStart = getOrInsertDeclaration(runtime->module, Intrinsic::vastart, {runtime->builder.getPtrTy()});
        runtime->builder.CreateCall(vaStart, {vaList});
        return vaList;
    }
    assert(0);
}

string LgsParam::getIRName() {
    if (const auto funcType = dynamic_cast<LgsFuncType*>(type)) {
        return funcType->IRName;
    }
    return name;
}

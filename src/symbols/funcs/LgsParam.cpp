#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"
#include "funcs/LgsFunc.h"
#include "types/LgsFuncType.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->prettyName();
}

Value* LgsParam::getIRValue(CodegenMetadata* metadata) {
    if (IRValue) return IRValue;
    if (isVariadic) {
        if (vaList) return vaList;
        vaList = metadata->builder.CreateAlloca(ptrTy);
        const auto vaStart = getOrInsertDeclaration(metadata->module, Intrinsic::vastart, {ptrTy});
        metadata->builder.CreateCall(vaStart, {vaList});
        return vaList;
    }
    return IRValue;
}

json LgsParam::asJSON() {
    json tree;
    tree["name"] = name;
    return tree;
}

string LgsParam::getIRName() {
    if (const auto funcType = dynamic_cast<LgsFuncType*>(type)) {
        return funcType->IRName;
    }
    return name;
}

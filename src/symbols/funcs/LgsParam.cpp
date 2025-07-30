#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->prettyName();
}

Value* LgsParam::getIRValue(LgsCodeGen* codeGen) {
    if (IRValue) return IRValue;
    if (isVariadic) {
        if (vaList) return vaList;
        vaList = codeGen->builder.CreateAlloca(codeGen->builder.getPtrTy());
        const auto vaStart = getOrInsertDeclaration(codeGen->IRModule, Intrinsic::vastart, {codeGen->builder.getPtrTy()});
        codeGen->builder.CreateCall(vaStart, {vaList});
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

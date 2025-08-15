#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"

void LgsParam::createIRValue(LgsCodeGen* codeGen) {
    if (IRValue) return;
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
    assert(0);
}

std::string LgsParam::format(std::string& indentStr) {
    return name + ": " + type->prettyName();
}


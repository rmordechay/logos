#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"

json::object LgsParam::asJSON() {
    json::object obj;
    return obj;
}

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

std::string LgsParam::format(std::string& indentStr) {
    return name + ": " + type->pname();
}


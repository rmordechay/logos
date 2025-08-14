#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"

std::string LgsParam::format(std::string& indentStr) {
    return name + ": " + type->prettyName();
}

Value* LgsParam::getIRValue(LgsCodeGen* codeGen) {
    if (IRValue) return IRValue;
    if (isVariadic) {
        if (vaList) return vaList;
        vaList = codeGen->builder.CreateAlloca(codeGen->builder.getPtrTy());
        const auto vaStart = Intrinsic::getDeclaration(codeGen->IRModule, Intrinsic::vastart, {codeGen->builder.getPtrTy()});
        codeGen->builder.CreateCall(vaStart, {vaList});
        return vaList;
    }
    assert(0);
}

std::string LgsParam::getIRName() {
    if (const auto funcType = dynamic_cast<LgsFuncType*>(type)) {
        return funcType->IRName;
    }
    return name;
}

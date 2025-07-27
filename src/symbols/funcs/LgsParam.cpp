#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->prettyName();
}

Value* LgsParam::getIRValue(LgsModule* module) {
    if (IRValue) return IRValue;
    if (isVariadic) {
        if (vaList) return vaList;
        vaList = module->builder.CreateAlloca(module->builder.getPtrTy());
        const auto vaStart = getOrInsertDeclaration(module->IRModule, Intrinsic::vastart, {module->builder.getPtrTy()});
        module->builder.CreateCall(vaStart, {vaList});
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

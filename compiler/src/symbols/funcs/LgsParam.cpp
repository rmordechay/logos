#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsCgModule.h"

Value* LgsParam::loadIR(LgsCgModule& cg) {
    if (IRValue->getType()->isPointerTy()) {
        return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
    }
    return IRValue;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

void freeParams(std::vector<LgsParam>& params) {
    for (const auto& param : params) {
        if (param.isSelf) continue;
        if (param.expr) {
            freeExpr(param.expr);
        } else if (param.type) {
            freeType(param.type);
        }
    }
    params.clear();
}

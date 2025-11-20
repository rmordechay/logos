#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsParam::loadIR(LgsLLVMGen& cg) {
    if (IRValue->getType()->isPointerTy()) {
        return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
    }
    return IRValue;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

LgsParam* LgsParam::clone() {
    const auto cloned = new LgsParam(type, name);
    cloned->location = location;
    if (expr) {
        cloned->expr = expr->clone();
    }
    cloned->isSelf = isSelf;
    cloned->isVariadic = isVariadic;
    return cloned;
}

void freeParams(std::vector<LgsParam>& params) {
    for (size_t i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        if (param.expr) {
            freeExpr(param.expr);
        } else if (param.type) {
            freeType(param.type);
        }
    }
    params.clear();
}

#include "funcs/LgsParam.h"
#include "LgsType.h"
#include "codegen/LgsCgModule.h"

Value* LgsParam::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsParam::setType(LgsType* newType) {
    type = newType;
}

void LgsParam::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

void freeParams(std::vector<LgsParam>& params) {
    for (const auto& param : params) {
        if (param.isSelf) continue;
        if (param.expr) {
            freeExpr(param.expr);
        }
        freeType(param.type);
    }
    params.clear();
}

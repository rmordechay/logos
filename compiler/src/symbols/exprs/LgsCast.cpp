#include "exprs/LgsCast.h"
#include "LgsType.h"
#include "LgsUtils.h"

Value* LgsCast::loadIR(LgsLLVMGen& cg) {
    return value->loadIR(cg);
}

std::string LgsCast::asText() {
    return fromValue->asText() + "->" + toType->pname();
}

Value* LgsCast::castIR(LgsLLVMGen& cg, LgsType* castToType) {
    assert(value->IRValue);
    return value->IRValue;
}

LgsCast::~LgsCast() {
    freeExpr(fromValue);
    freeType(toType);
    fromValue = nullptr;
    toType = nullptr;
}

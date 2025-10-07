#include "exprs/constants/LgsStrConst.h"

LgsExpr* LgsStrConst::castTo(LgsType* toType, bool explicitCast) {
    return LgsExpr::castTo(toType, explicitCast);
}

Value* LgsStrConst::castToIR(LgsLLVMGen& cg, LgsType* toType) {
    return LgsExpr::castToIR(cg, toType);
}

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsStrConst::getName() {
    return '"' + value + '"';
}

Value* LgsStrConst::hash(LgsLLVMGen& cg) {
    return cg.i32(hashStr(value.c_str()));
}

void LgsStrConst::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "IntConst", true);
    addJsonKeyValue(json, "value", value);
    closeJsonObject(json);
}

LgsStrConst::~LgsStrConst() {
    if (formatedStr != "") {
        // delete formatedStr.c_str();
        // formatedStr = "";
    }
}

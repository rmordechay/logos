#include "exprs/constants/LgsStrConst.h"

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsStrConst::eqIR(LgsLLVMGen& cg, Value* other) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {IRValue, other});
    return cg.builder.CreateICmpEQ(rt, cg.i32(0));
}

std::string LgsStrConst::getName() {
    return '"' + value + '"';
}

Value* LgsStrConst::hash(LgsLLVMGen& cg) {
    return cg.i32(hashStr(value.c_str()));
}

json::value LgsStrConst::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprType"] = "strConst";
    jsonObj["value"] = value;
    jsonObj["type"] = type->asJsonStr();
    return jsonObj;
}

LgsStrConst::~LgsStrConst() {
    if (formatedStr != "") {
        // delete formatedStr.c_str();
        // formatedStr = "";
    }
}

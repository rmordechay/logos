#include "exprs/constants/LgsStrConst.h"

Value* LgsStrConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsStrConst::pname() {
    return '"' + value + '"';
}

Value* LgsStrConst::hash(LgsLLVMGen& cg) {
    return cg.i32(hashStr(value.c_str()));
}

json::value LgsStrConst::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "strConst";
    jsonObj["value"] = value;
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}

LgsExpr* LgsStrConst::clone() {
    return new LgsStrConst(*this);
}

LgsStrConst::~LgsStrConst() {
    if (formatedStr != "") {
        // delete formatedStr.c_str();
        // formatedStr = "";
    }
}

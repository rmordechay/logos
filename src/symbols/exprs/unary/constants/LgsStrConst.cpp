#include "exprs/unary/constants/LgsStrConst.h"

std::string LgsStrConst::pname() {
    return value.substr(0, 50) + "...";
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

Value* LgsStrConst::eqIR(LgsLLVMGen& cg, LgsExpr* other) {
    return nullptr;
}

Value* LgsStrConst::addIR(LgsLLVMGen& cg, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return cg.getIRStr(this->value + std::to_string(otherStrConst->value));
    }
    assert(0);
}

LgsExpr* LgsStrConst::clone() {
    return new LgsStrConst(*this);
}

LgsExpr* LgsStrConst::castTo(LgsType* toType) {
    if (type->asStr()) return this;
    assert(0);
}

LgsStrConst::~LgsStrConst() {
    if (formatedStr != "") {
        delete formatedStr.c_str();
        formatedStr = "";
    }
}

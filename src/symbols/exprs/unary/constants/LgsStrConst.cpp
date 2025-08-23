#include "exprs/unary/constants/LgsStrConst.h"

std::string LgsStrConst::pname() {
    return type->pname();
}

Value* LgsStrConst::hash(LgsCodeGen& codeGen) {
    return codeGen.i32(hashStr(value.c_str()));
}

json::value LgsStrConst::asJSON() {
    json::object jsonObj;
    jsonObj["exprType"] = "strConst";
    jsonObj["value"] = value;
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}

Value* LgsStrConst::eqIR(LgsCodeGen& codeGen, LgsExpr* other) {
    return nullptr;
}

Value* LgsStrConst::addIR(LgsCodeGen& codeGen, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return codeGen.getIRStr(this->value + std::to_string(otherStrConst->value));
    }
    assert(0);
}

LgsExpr* LgsStrConst::clone() {
    return new LgsStrConst(*this);
}

LgsStrConst::~LgsStrConst() {
    if (formatedStr != "") {
        delete formatedStr.c_str();
        formatedStr = "";
    }
}

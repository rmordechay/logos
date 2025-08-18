#include "exprs/unary/constants/LgsIntConst.h"

void LgsIntConst::setNumberType() {
    if (type->asBool()) {
        numberType = LgsNumberType::I1;
    } else if (type->asChar()) {
        numberType = LgsNumberType::I8;
    } else if (type->asShort()) {
        numberType = LgsNumberType::I16;
    } else if (type->asInt()) {
        numberType = LgsNumberType::I32;
    } else if (type->asInt()) {
        numberType = LgsNumberType::I64;
    } else {
        assert(0);
    }
}

void LgsIntConst::createIRValue(LgsCodeGen* codeGen) {
    switch (numberType) {
    case LgsNumberType::I1:
        IRValue = codeGen->i1(value);
        break;
    case LgsNumberType::I8:
        IRValue = codeGen->i8(value);
        break;
    case LgsNumberType::I16:
        IRValue = codeGen->i16(value);
        break;
    case LgsNumberType::I32:
        IRValue = codeGen->i32(value);
        break;
    case LgsNumberType::I64:
        IRValue = codeGen->i64(value);
        break;
    }
}

std::string LgsIntConst::pname() {
    return type->getName() + "(" + std::to_string(value) + ")";
}

json::object LgsIntConst::asJSON() {
    json::object obj;
    return obj;
}

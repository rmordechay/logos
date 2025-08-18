#include "exprs/unary/constants/LgsIntConst.h"

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

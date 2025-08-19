#include "../../../include/symbols/exprs/unary/LgsVectorExpr.h"

std::string LgsVec::getName() {
    return "vec" + std::to_string(dim);
}

json::object LgsVec::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsVec::pname() {
    return getName();
}

Type* LgsVec::getIRType(LgsCodeGen* codeGen) {
    IRType = FixedVectorType::get(baseType->getIRType(codeGen), 2);
    return IRType;
}

size_t LgsVec::getSizeBytes() {
    return baseType->getSizeBytes() * 2;
}

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr();
}

LgsType* LgsVec::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsVec::getUnpackCount() const {
    return 1;
}

Value* LgsVec::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->isize(2);
}

Value* LgsVec::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getFalse();
}

Value* LgsVec::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getTrue();
}

bool LgsVec::equals(LgsType* other) {
    assert(0);
}

std::string LgsVec::strFormatPart() const {
    return "%s";
}
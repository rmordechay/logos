#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsVectorExpr.h"

Type* LgsVec::getIRType(LgsLLVM& codeGen) {
    IRType = FixedVectorType::get(baseType->getIRType(codeGen), 2);
    return IRType;
}

LgsField* LgsVec::getField(const std::string& fieldName) {
    const auto fieldType = dim == 1 ? baseType : new LgsVec(dim);
    const auto field = new LgsField(fieldName, fieldType);
    addField(field);
    return field;
}

std::string LgsVec::getName() {
    return "vec" + std::to_string(dim);
}

std::string LgsVec::pname() {
    return getName();
}

json::value LgsVec::asJSON() {
    assert(0);
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

Value* LgsVec::IRLength(LgsLLVM& codeGen, LgsExpr* iterable) {
    return codeGen.isize(2);
}

Value* LgsVec::IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getFalse();
}

Value* LgsVec::IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getTrue();
}

bool LgsVec::canCastTo(LgsType* other) {
    assert(0);
}

int8_t LgsVec::getSwizzleSet(const char c) {
    if (strchr("xyzw", c)) return 0;
    if (strchr("rgba", c)) return 1;
    if (strchr("stpq", c)) return 2;
    return -1;
}

int8_t LgsVec::getComponentIndex(const char c) {
    switch (c) {
    case 'x': case 'r': case 's': return 0;
    case 'y': case 'g': case 't': return 1;
    case 'z': case 'b': case 'p': return 2;
    case 'w': case 'a': case 'q': return 3;
    default: return -1;
    }
}

std::string LgsVec::strFormatPart() const {
    return baseType->strFormatPart();
}

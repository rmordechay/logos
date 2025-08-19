#include "../../../include/symbols/types/LgsVoid.h"

#include "exprs/LgsNull.h"


json::value_ref LgsVoid::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsVoid::pname() {
    return name;
}

Type* LgsVoid::getIRType(LgsCodeGen* codeGen) {
    return Type::getVoidTy(codeGen->context);
}

size_t LgsVoid::getSizeBytes() {
    return 0;
}

std::string LgsVoid::getName() {
    return name;
}

LgsExpr* LgsVoid::getZeroValue() {
    return nullptr;
}

std::string LgsVoid::strFormatPart() const {
    assert(0);
}

bool LgsVoid::equals(LgsType* other) {
    return name == other->getName();
}

#include "types/primitives/LgsSize.h"

#include "types/LgsAny.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

size_t LgsSize::getSizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsCodeGen* codeGen) {
    return codeGen->sizeTy();
}

std::string LgsSize::getName() {
    return name;
}

json::value_ref LgsSize::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsSize::pname() {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    assert(0);
}

bool LgsSize::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsFloat::name) return true;
    if (IRName == LgsLong::name) return true;
    return name == IRName;
}

std::string LgsSize::strFormatPart() const {
    return "%zu";
}
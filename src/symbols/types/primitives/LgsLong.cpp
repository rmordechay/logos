#include "types/primitives/LgsLong.h"

#include "exprs/unary/constants/LgsIntConst.h"
#include "types/LgsAny.h"
#include "types/LgsCPtr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsSize.h"

json::object LgsLong::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsLong::pname() {
    return name;
}

Type* LgsLong::getIRType(LgsCodeGen* codeGen) {
    return codeGen->i64Ty();
}

size_t LgsLong::getSizeBytes() {
    return sizeof(long);
}

LgsExpr* LgsLong::getZeroValue() {
    return new LgsIntConst(&LGS_LONG, 0);
}

std::string LgsLong::getName() {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsFloat::name) return true;
    return name == IRName;
}

std::string LgsLong::strFormatPart() const {
    return "%lu";
}

#include "types/primitives/LgsInt.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsCPtr.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"


size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

Type* LgsInt::getIRType(LgsCodeGen* codeGen) {
    return codeGen->i32Ty();
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

bool LgsInt::equals(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsBool::name) return true;
    if (otherName == LgsChar::name) return true;
    if (otherName == LgsShort::name) return true;
    if (otherName == LgsFloat::name) return true;
    return name == otherName;
}

std::string LgsInt::strFormatPart() const {
    return "%d";
}

std::string LgsInt::getName() {
    return name;
}

std::string LgsInt::pname() {
    return getName();
}

json::value LgsInt::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

LgsType* LgsInt::clone() {
    return this;
}

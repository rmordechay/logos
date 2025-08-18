#include "types/primitives/LgsInt.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsCPtr.h"
#include "types/primitives/LgsFloat.h"
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
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsUInt::name) return true;
    if (IRName == LgsSize::name) return true;
    if (IRName == LgsLong::name) return true;
    if (IRName == LgsFloat::name) return true;
    return name == IRName;
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

json::object LgsInt::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

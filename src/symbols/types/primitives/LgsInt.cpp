#include "types/primitives/LgsInt.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

#include <llvm/IR/DIBuilder.h>

size_t LgsInt::getSizeBytes() {
    return sizeof(int);
}

Type* LgsInt::getIRType(LgsLLVM& codeGen) {
    return codeGen.i32Ty();
}

LgsExpr* LgsInt::getZeroValue() {
    return new LgsIntConst(&LGS_INT, 0);
}

bool LgsInt::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (name == otherName) return true;
    if (otherName == LgsAny::name) return true;
    if (otherName == LgsFloat::name) return true;
    if (otherName == LgsDouble::name) return true;
    return false;
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

DIBasicType* LgsInt::getDebugType(LgsLLVM& codeGen) {
    return codeGen.diBuilder->createBasicType(name, 32, dwarf::DW_ATE_signed);
}

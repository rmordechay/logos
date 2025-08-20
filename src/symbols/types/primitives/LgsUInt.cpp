#include "types/primitives/LgsUInt.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "logos/LgsCodeGen.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

size_t LgsUInt::getSizeBytes() {
    return sizeof(uint32_t);
}

json::value LgsUInt::asJSON() {
    assert(0);
}

std::string LgsUInt::pname() {
    return name;
}

llvm::Type* LgsUInt::getIRType(LgsCodeGen* codeGen) {
    return codeGen->i32Ty();
}

std::string LgsUInt::getName() {
    return name;
}

LgsExpr* LgsUInt::getZeroValue() {
    return new LgsIntConst(this, 0);
}

bool LgsUInt::equals(LgsType* other) {
    const auto IRName = other->getName();
    if (IRName == LgsAny::name) return true;
    if (IRName == LgsInt::name) return true;
    if (IRName == LgsSize::name) return true;
    return name == IRName;
}

std::string LgsUInt::strFormatPart() const {
    return "%d";
}

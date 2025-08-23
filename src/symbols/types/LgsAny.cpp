#include "types/LgsAny.h"
#include "codegen/LgsCodeGen.h"

size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsCodeGen& codeGen) {
    return codeGen.ptrTy();
}

std::string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

json::value LgsAny::asJSON() {
    assert(0);
}

std::string LgsAny::pname() {
    return name;
}

std::string LgsAny::strFormatPart() const {
    return "%p";
}

bool LgsAny::canCastTo(LgsType* other) {
    return true;
}

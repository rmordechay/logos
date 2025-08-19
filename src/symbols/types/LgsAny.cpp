#include "types/LgsAny.h"
#include "logos/LgsCodeGen.h"

size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

std::string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

json::value_ref LgsAny::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsAny::pname() {
    return name;
}

std::string LgsAny::strFormatPart() const {
    return "%p";
}

bool LgsAny::equals(LgsType* other) {
    return true;
}

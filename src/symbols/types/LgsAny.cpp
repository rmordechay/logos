#include "types/LgsAny.h"
#include "logos/LgsCodeGen.h"

size_t LgsAny::getSizeBytes() {
    return sizeof(void*);
}

Type* LgsAny::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

string LgsAny::getName() {
    return name;
}

LgsExpr* LgsAny::getZeroValue() {
    assert(0);
}

string LgsAny::prettyName() {
    return name;
}

string LgsAny::strFormatPart() const {
    return "%p";
}

bool LgsAny::equals(LgsType* other) {
    return true;
}

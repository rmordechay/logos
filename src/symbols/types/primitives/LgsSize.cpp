#include "types/primitives/LgsSize.h"
#include "logos/LgsRuntime.h"
#include "logos/Platform.h"

size_t LgsSize::getSizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType() {
    return dataLayout.getIntPtrType(context);
}

std::string LgsSize::getIRName() {
    return name;
}

std::string LgsSize::prettyName() const {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    assert(0);
}

bool LgsSize::equals(LgsType* other) {
    assert(0);
}

std::string LgsSize::getStrFormatPart() const {
    return "%zu";
}
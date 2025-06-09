#include "types/primitives/LgsSize.h"

#include "logos/LgsRuntime.h"
#include "utils/LgsUtils.h"

size_t LgsSize::getSizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType() {
    return getTargetMachine()->createDataLayout().getIntPtrType(context);
}

std::string LgsSize::getIRName() {
    return name;
}

std::string LgsSize::prettyName() const {
    return name;
}

LgsExpr* LgsSize::getZeroValue() {
    assert(false);
}

bool LgsSize::equals(LgsType* other) {
    assert(false);
}

std::string LgsSize::getStrFormatPart() const {
    return "%zu";
}

LgsType* LgsSize::clone() {
    return LgsType::clone();
}

LgsType* LgsSize::inferBinaryType(LgsType* other) {
    assert(false);
}

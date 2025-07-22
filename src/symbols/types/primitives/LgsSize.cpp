#include "types/primitives/LgsSize.h"
#include "logos/LgsModule.h"

size_t LgsSize::getSizeBytes() {
    return sizeof(size_t);
}

Type* LgsSize::getIRType(LgsModule* module) {
    return dataLayout.getIntPtrType(module->context);
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
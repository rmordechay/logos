#include "exprs/unary/LgsDArray.h"
#include "types/LgsDArrType.h"

Value* LgsDArray::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

size_t LgsDArray::length() const {
    return initialElements.size();
}

void LgsDArray::free(CodeGenMetadata* metadata) {

}

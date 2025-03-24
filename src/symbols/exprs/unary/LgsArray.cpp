#include "exprs/unary/LgsArray.h"

#include <loops/LgsLoop.h>

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    vector<Constant*> arrValues;
    for (const auto & element : elements) {
        arrValues.emplace_back(static_cast<Constant*>(element->getIRValue(metadata)));
    }
    const auto arrayType = type->getIRType(elements.size());
    const auto arrType = ArrayType::get(arrayType, elements.size());
    return createIRGlobal(metadata->currentModule, ConstantArray::get(arrType, arrValues));
}

size_t LgsArray::size() {
    return elements.size();
}
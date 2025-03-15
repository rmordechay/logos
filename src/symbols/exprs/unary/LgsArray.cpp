#include "unary/LgsArray.h"

#include <loops/LogosLoop.h>

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    vector<Constant*> arrValues;
    for (const auto & element : elements) {
        arrValues.emplace_back(static_cast<Constant*>(element->getIRValue(metadata)));
    }
    const auto arrType = ArrayType::get(type->getIRType(), elements.size());
    return ConstantArray::get(arrType, arrValues);
}


size_t LgsArray::size() {
    return elements.size();
}

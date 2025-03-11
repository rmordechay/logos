#include "unary/LogosArray.h"

Value* LogosArray::createIRValue(CodeGenMetadata* metadata) {
    vector<Constant*> arrValues;
    for (const auto & element : elements) {
        arrValues.emplace_back(static_cast<Constant*>(element->getIRValue(metadata)));
    }
    const auto arrType = ArrayType::get(type->getIRType(), elements.size());
    const auto array = ConstantArray::get(arrType, arrValues);
    return new GlobalVariable(*metadata->currentModule, arrType, true, privateLinkage, array);
}

size_t LogosArray::size() {
    return elements.size();
}

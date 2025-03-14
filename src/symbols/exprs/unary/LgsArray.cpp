#include "unary/LgsArray.h"

Value* LgsArray::createIRValue(CodeGenMetadata* metadata) {
    vector<Constant*> arrValues;
    for (const auto & element : elements) {
        arrValues.emplace_back(static_cast<Constant*>(element->getIRValue(metadata)));
    }
    const auto arrType = ArrayType::get(type->getIRType(), elements.size());
    const auto array = ConstantArray::get(arrType, arrValues);
    return new GlobalVariable(*metadata->currentModule, arrType, true, privateLinkage, array);
}

size_t LgsArray::size() {
    return elements.size();
}

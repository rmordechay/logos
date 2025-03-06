#include "exprs//LogosArray.h"

#include <llvm/IR/Module.h>

Value* LogosArray::computeIRValue(CodeGenMetadata* metadata) {
    vector<Constant*> arrValues;
    for (const auto & element : elements) {
        arrValues.emplace_back(static_cast<Constant*>(element->writeIRValue(metadata)));
    }
    const auto arrType = ArrayType::get(type->getIRType(), elements.size());
    const auto array = ConstantArray::get(arrType, arrValues);
    return new GlobalVariable(*metadata->currentModule, arrType, true, GlobalValue::PrivateLinkage, array);
}
#include "exprs//LogosArray.h"

Value* LogosArray::computeIRValue(CodeGenMetadata* metadata) {
    vector<Value*> arrElements;
    for (const auto & element : elements) {
        arrElements.emplace_back(element->getIRValue(metadata));
    }
    const auto arrType = ArrayType::get(type->getIRType(), elements.size());
    return  metadata->module->getOrInsertGlobal("array", arrType);
}

LogosSymbolType LogosArray::getSymbolType() {
    return ARRAY;
}

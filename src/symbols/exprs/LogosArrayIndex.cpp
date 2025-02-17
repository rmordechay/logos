#include "exprs/LogosArrayIndex.h"

Value* LogosArrayIndex::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

LogosSymbolType LogosArrayIndex::getSymbolType() {
    return ARRAY_INDEX;
}

string LogosArrayIndex::getName() {

}

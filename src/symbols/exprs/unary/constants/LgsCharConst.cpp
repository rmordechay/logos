#include "exprs/unary/constants/LgsCharConst.h"

Value* LgsCharConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt8(value);
}

#include "exprs/unary/constants/LgsCharConst.h"

Value* LgsCharConst::createIRValue(CodegenMetadata* metadata) {
    return metadata->builder.getInt8(value);
}

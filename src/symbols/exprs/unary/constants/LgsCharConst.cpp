#include "constants/LgsCharConst.h"


Value* LgsCharConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt1(value);
}

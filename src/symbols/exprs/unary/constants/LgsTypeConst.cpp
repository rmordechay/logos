#include "constants/LgsTypeConst.h"

#include "AntlrConverter.h"

string LgsTypeConst::getName() {
    return type->getName();
}

Value* LgsTypeConst::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

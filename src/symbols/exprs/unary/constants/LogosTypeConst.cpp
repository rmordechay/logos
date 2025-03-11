#include "constants/LogosTypeConst.h"

#include "AntlrConverter.h"

string LogosTypeConst::getName() {
    return type->getName();
}

Value* LogosTypeConst::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

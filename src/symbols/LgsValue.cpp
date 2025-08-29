#include "LgsValue.h"
#include "funcs/LgsFunc.h"

Value* LgsValue::loadIR(LgsLLVMGen& cg) {
    assert(IRValue);
    return cg.builder.CreateLoad(IRValue->getType(), IRValue);
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

void LgsValue::setDebugValue(LgsLLVMGen& cg) {
    assert(0);
}

DILocation* LgsValue::getDebugLoc(LgsLLVMGen& cg) const {
    return DILocation::get(
        cg.context,
        location.lineStart,
        location.posInLine,
        cg.diProgram,
        cg.diProgram->getScope()
    );
}
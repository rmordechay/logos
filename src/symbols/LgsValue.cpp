#include "LgsValue.h"

#include "codegen/LgsLLVMGen.h"

Value* LgsValue::loadIR(LgsLLVMGen& cg) {
    assert(0);
}

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

std::string LgsValue::pname() {
    assert(0);
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
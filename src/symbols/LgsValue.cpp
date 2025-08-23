#include "LgsValue.h"
#include "funcs/LgsFunc.h"

void LgsValue::setIRValue(Value* value) {
    IRValue = value;
}

void LgsValue::setDebugValue(LgsCodeGen& codeGen) {
    assert(0);
}

DILocation* LgsValue::getDebugLoc(LgsCodeGen& codeGen) const {
    return DILocation::get(
        codeGen.context,
        location.lineStart,
        location.posInLine,
        codeGen.diProgram,
        codeGen.diProgram->getScope()
    );
}
#include "LgsValue.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsValue::loadIR(LgsLLVMGen& cg) {
    assert(0);
}

std::string LgsValue::getName() {
    assert(0);
}

void LgsValue::parseAsJSON(std::stringstream& json) {
    assert(0);
}

void LgsValue::setDebugValue(LgsLLVMGen& cg) {
    assert(0);
}

DILocation* LgsValue::getDebugLoc(LgsLLVMGen& cg) const {
    return DILocation::get(
        cg.context,
        location.lineStart,
        location.columnStart,
        cg.diProgram,
        cg.diProgram->getScope()
    );
}
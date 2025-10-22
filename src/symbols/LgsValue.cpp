#include "LgsValue.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsValue::loadIR(LgsLLVMGen& cg) {
    assert(0);
}

std::string LgsValue::asText() {
    assert(0);
}

void LgsValue::setDebugValue(LgsLLVMGen& cg) {
    assert(0);
}

void LgsValue::hashValue(size_t& oldHash) {
    assert(0);
}

DILocation* LgsValue::getDebugLoc(LgsLLVMGen& cg) const {
    return DILocation::get(
        cg.context,
        location.lineStart,
        location.columnStart,
        cg.debugger.diProgram,
        cg.debugger.diProgram->getScope()
    );
}

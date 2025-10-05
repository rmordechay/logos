#include "LgsValue.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsValue::loadIR(LgsLLVMGen& cg) {
    assert(0);
}

Value* LgsValue::addIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::subIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::mulIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::divIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::eqIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::neIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::ltIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::gtIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::geIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::leIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::andIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

Value* LgsValue::orIR(LgsLLVMGen& cg, Value* other) {
    assert(0);
}

std::string LgsValue::getName() {
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
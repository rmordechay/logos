#include "types/iterables/LgsVariadic.h"

size_t LgsVariadic::sizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsVariadic::getZeroValue() {
    assert(0);
}

Type* LgsVariadic::getIRType(LgsCodeGen& cg) {
    return baseType->getIRType(cg);
}

bool LgsVariadic::canCastTo(LgsType* other) {
    assert(0);
}

LgsType* LgsVariadic::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsVariadic::fmtStr() const {
    assert(0);
}

DIType* LgsVariadic::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsVariadic::getBaseName() {
    return name;
}

std::string LgsVariadic::getName() {
    return baseType->getName() + "...";
}

bool LgsVariadic::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsVariadic::lenIR(LgsCodeGen& cg, Value* iterable) {
    assert(cg.currentFunc->arg_size() > 1);
    return cg.currentFunc->getArg(cg.currentFunc->arg_size() - 2);
}

Value* LgsVariadic::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    assert(0);
}

Value* LgsVariadic::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    return cg.builder.CreateVAArg(iterable, baseType->getIRType(cg));
}

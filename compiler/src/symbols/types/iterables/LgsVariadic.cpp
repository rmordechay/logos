#include "types/iterables/LgsVariadic.h"

#include <llvm/IR/Argument.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <cassert>

#include "codegen/LgsCodeGen.h"
#include "LgsType.h"

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
    if (other->isAny()) return true;
    assert(0);
}

LgsType* LgsVariadic::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsVariadic::fmtStr() const {
    assert(0);
}

Constant* LgsVariadic::getRTTypeExtra(LgsCodeGen& cg) {
    return baseType->getRTType(cg);
}

DIType* LgsVariadic::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsVariadic::getBaseName() {
    return name;
}

std::string LgsVariadic::getName() {
    return name + baseType->getName();
}

std::string LgsVariadic::pname() {
    return baseType->pname() + "...";
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

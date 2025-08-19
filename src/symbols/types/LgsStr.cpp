#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"

Type* LgsStr::getIRBaseType(LgsCodeGen* codeGen) const {
    return ArrayType::get(baseType->getIRType(codeGen), sizeExpr->getConstInt());
}

Type* LgsStr::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

uint16_t LgsStr::getUnpackCount() const {
    return 1;
}

std::string LgsStr::getName() {
    return name;
}

json::value_ref LgsStr::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsStr::pname() {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

std::string LgsStr::strFormatPart() const {
    return "%s";
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

Value* LgsStr::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return lenFunc->call(codeGen, {iterable});
}

Value* LgsStr::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(codeGen, {iterable});
}

Value* LgsStr::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(codeGen, {iterable});
}

bool LgsStr::equals(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto iter = other->asIterable()) {
        return iter->baseType && iter->baseType->asChar();
    }
    return name == other->getName();
}

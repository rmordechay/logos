#include "types/LgsTable.h"
#include "builtins/LgsSystem.h"
#include "exprs/unary/LgsTableExpr.h"

std::string LgsTable::pname() {
    return getName();
}

llvm::Type* LgsTable::getIRType(LgsCodeGen* codeGen) {
    return codeGen->ptrTy();
}

size_t LgsTable::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsTable::getZeroValue() {
    return new LgsTableExpr(this);
}

std::string LgsTable::getName() {
    return name;
}

bool LgsTable::equals(LgsType* other) {
    assert(0);
}

std::string LgsTable::strFormatPart() const {
    return "%s";
}

json::value_ref LgsTable::asJSON() {
    json::object obj;
    return obj;
}

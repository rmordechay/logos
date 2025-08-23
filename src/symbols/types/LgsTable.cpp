#include "types/LgsTable.h"
#include "builtins/LgsSystem.h"

std::string LgsTable::pname() {
    return getName();
}

llvm::Type* LgsTable::getIRType(LgsCodeGen& codeGen) {
    const auto fieldsArrType = ArrayType::get(codeGen.ptrTy(), fields.size());
    const auto tableFieldType = codeGen.getStructType({codeGen.ptrTy(), codeGen.ptrTy()}, "Table_Field");
    return codeGen.getStructType({fieldsArrType, tableFieldType}, "Table");
}

size_t LgsTable::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsTable::getZeroValue() {
    assert(0);
}

std::string LgsTable::getName() {
    return name;
}

bool LgsTable::canCastTo(LgsType* other) {
    assert(0);
}

std::string LgsTable::strFormatPart() const {
    return "%s";
}

json::value LgsTable::asJSON() {
    assert(0);
}

LgsTable::~LgsTable() {
    freeExpr(instance);
    instance = nullptr;
}

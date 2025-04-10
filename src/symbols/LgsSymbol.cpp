#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

LgsSymbol::LgsSymbol(): type(UNKNOWN), object(nullptr) {}
LgsSymbol::LgsSymbol(LgsParam* param): type(PARAM), param(param) {}
LgsSymbol::LgsSymbol(LgsVarDec* varDec): type(VAR_DEC), varDec(varDec) {}
LgsSymbol::LgsSymbol(LgsFunc* func): type(FUNC), func(func) {}
LgsSymbol::LgsSymbol(LgsObject* object): type(OBJECT), object(object) {}
LgsSymbol::LgsSymbol(LgsInterface* interface): type(INTERFACE), interface(interface) {}
LgsSymbol::LgsSymbol(LgsEnum* lgsEnum): type(ENUM), lgsEnum(lgsEnum) {}
LgsSymbol::LgsSymbol(LgsEnumField* enumField): type(ENUM_FIELD), enumField(enumField) {}

void LgsSymbol::free(CodeGenMetadata* metadata) const {
    switch (type) {
    case VAR_DEC:
        varDec->free(metadata);
        break;
    default:
        assert(false);
    }
}

#include "LgsSymbol.h"
#include "stmts/LgsEnum.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsObject.h"

LgsSymbol::LgsSymbol():
    type(static_cast<LgsSymbolType>(0)),
    object(nullptr) {
}

LgsSymbol::LgsSymbol(const LgsSymbolType type, LgsParam* param):
    type(type),
    param(param) {
}

LgsSymbol::LgsSymbol(const LgsSymbolType type, LgsVarDec* varDec):
    type(type),
    varDec(varDec) {
}

LgsSymbol::LgsSymbol(const LgsSymbolType type, LgsFunc* funcImpl):
    type(type),
    func(funcImpl) {
}

LgsSymbol::LgsSymbol(const LgsSymbolType type, LgsObject* object):
    type(type),
    object(object) {
}

LgsSymbol::LgsSymbol(const LgsSymbolType type, LgsInterface* interface):
    type(type),
    interface(interface) {
}

LgsSymbol::LgsSymbol(const LgsSymbolType type, LgsEnum* lgsEnum):
    type(type),
    lgsEnum(lgsEnum) {
}

void LgsSymbol::free(CodeGenMetadata* metadata) const {
    switch (type) {
    case VAR_DEC:
        varDec->free(metadata);
        break;
    case ENUM:
        lgsEnum->free(metadata);
        break;
    default:
        break;
    }
}

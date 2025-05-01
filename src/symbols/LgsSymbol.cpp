#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"

LgsSymbol::LgsSymbol(): type(UNKNOWN) {}
LgsSymbol::LgsSymbol(LgsParam* param): type(PARAM), param(param) {}
LgsSymbol::LgsSymbol(LgsVarDec* varDec): type(VAR_DEC), varDec(varDec) {}
LgsSymbol::LgsSymbol(const std::vector<LgsFunc*>& func): type(FUNC), func(func) {}
LgsSymbol::LgsSymbol(LgsObject* object): type(OBJECT), object(object) {}
LgsSymbol::LgsSymbol(LgsInterface* interface): type(INTERFACE), interface(interface) {}
LgsSymbol::LgsSymbol(LgsField* field): type(FIELD), field(field) {}
LgsSymbol::LgsSymbol(LgsEnum* lgsEnum): type(ENUM), lgsEnum(lgsEnum) {}
LgsSymbol::LgsSymbol(LgsEnumField* enumField): type(ENUM_FIELD), enumField(enumField) {}

void LgsSymbol::free(CodeGenMetadata* metadata) const {
    switch (type) {
    case VAR_DEC:
        varDec->free(metadata);
        break;
    default: assert(false);
    }
}

LgsSymbol* LgsSymbol::clone() const {
    return new LgsSymbol(*this);
}

Location* LgsSymbol::getSymbolLocation() const {
    switch (type) {
    case VAR_DEC:
        return &varDec->location;
    case PARAM:
        return &param->location;
    case FUNC:
        assert(false);
    default:
        return nullptr;
    }
}

json LgsSymbol::asJSON() const {
    json tree;
    switch (type) {
    case VAR_DEC:
        tree["type"] = "VAR_DEC";
        break;
    case PARAM:
        tree["type"] = "PARAM";
        break;
    case OBJECT:
        tree["type"] = "OBJECT";
        break;
    case INTERFACE:
        tree["type"] = "INTERFACE";
        break;
    case FIELD:
        tree["type"] = "FIELD";
        break;
    case FUNC:
        tree["type"] = "FUNC";
        break;
    case ENUM:
        tree["type"] = "ENUM";
        break;
    case ENUM_FIELD:
        tree["type"] = "ENUM_FIELD";
        break;
    case UNKNOWN:
        tree["type"] = "UNKNOWN";
        break;
    }
    return tree;
}

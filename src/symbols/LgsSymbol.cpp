#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

LgsSymbol::LgsSymbol(): symbolType(UNKNOWN) {}
LgsSymbol::LgsSymbol(LgsParam* param): symbolType(PARAM), param(param) {}
LgsSymbol::LgsSymbol(LgsVarDec* varDec): symbolType(VAR_DEC), varDec(varDec) {}
LgsSymbol::LgsSymbol(LgsObject* object): symbolType(OBJECT), object(object) {}
LgsSymbol::LgsSymbol(LgsInterface* interface): symbolType(INTERFACE), interface(interface) {}
LgsSymbol::LgsSymbol(LgsField* field): symbolType(FIELD), field(field) {}
LgsSymbol::LgsSymbol(LgsEnum* lgsEnum): symbolType(ENUM), lgsEnum(lgsEnum) {}
LgsSymbol::LgsSymbol(LgsEnumField* enumField): symbolType(ENUM_FIELD), enumField(enumField) {}
LgsSymbol::LgsSymbol(LgsFunc* func): symbolType(FUNC), func(func) {}
LgsSymbol::LgsSymbol(LgsGroup* group): symbolType(GROUP), group(group) {}

void* LgsSymbol::getPtr() const {
    switch (symbolType) {
    case VAR_DEC:
        return varDec;
    case PARAM:
        return param;
    case FUNC:
        return func;
    case OBJECT:
        return object;
    case INTERFACE:
        return interface;
    case FIELD:
        return field;
    case ENUM:
        return lgsEnum;
    case ENUM_FIELD:
        return enumField;
    case GROUP:
        return group;
    case UNKNOWN:
        break;
    }
    assert(0);
}

Location* LgsSymbol::getLocation() const {
    switch (symbolType) {
    case VAR_DEC:
        return &varDec->location;
    case PARAM:
        return &param->location;
    case FUNC:
        return &func->location;
    case OBJECT:
        return &object->location;
    case INTERFACE:
        return &interface->location;
    case FIELD:
        return &field->location;
    case ENUM:
        return &lgsEnum->location;
    case ENUM_FIELD:
        return &enumField->location;
    case GROUP:
        return &group->location;
    case UNKNOWN:
        break;
    }
    assert(0);
}

json LgsSymbol::asJSON() const {
    json tree;
    switch (symbolType) {
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
    case GROUP:
        tree["type"] = "GROUP";
        break;
    case UNKNOWN:
        tree["type"] = "UNKNOWN";
        break;
    }
    return tree;
}

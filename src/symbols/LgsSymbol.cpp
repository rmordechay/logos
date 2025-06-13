#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

LgsSymbol::LgsSymbol(): symbolType(UNKNOWN), location(nullptr) {}
LgsSymbol::LgsSymbol(LgsParam* param): symbolType(PARAM), location(&param->location), param(param) {}
LgsSymbol::LgsSymbol(LgsVarDec* varDec): symbolType(VAR_DEC), location(&varDec->location), varDec(varDec) {}
LgsSymbol::LgsSymbol(LgsObject* object, const bool isExternal): symbolType(OBJECT), location(&object->location), object(object), isExternal(isExternal) {}
LgsSymbol::LgsSymbol(LgsInterface* interface): symbolType(INTERFACE), location(&interface->location), interface(interface) {}
LgsSymbol::LgsSymbol(LgsField* field): symbolType(FIELD), location(&field->location), field(field) {}
LgsSymbol::LgsSymbol(LgsEnum* lgsEnum, const bool isExternal): symbolType(ENUM), location(&lgsEnum->location), lgsEnum(lgsEnum), isExternal(isExternal) {}
LgsSymbol::LgsSymbol(LgsEnumField* enumField): symbolType(ENUM_FIELD), location(&enumField->location), enumField(enumField) {}
LgsSymbol::LgsSymbol(LgsFunc* func, const bool isExternal): symbolType(FUNC), location(&func->location), func(func), isExternal(isExternal) {}
LgsSymbol::LgsSymbol(LgsGroup* group): symbolType(GROUP), location(&group->location), group(group) {}

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
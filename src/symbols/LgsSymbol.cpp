#include "LgsSymbol.h"

#include "exprs/unary/LgsEnumField.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

LgsSymbol::LgsSymbol(): symbolType(UNKNOWN), location(nullptr) {}

LgsSymbol::LgsSymbol(LgsParam* param): symbolType(PARAM), param(param), location(&param->location) {}

LgsSymbol::LgsSymbol(LgsVarDec* varDec): symbolType(VAR_DEC), varDec(varDec), location(&varDec->location) {}

LgsSymbol::LgsSymbol(LgsObject* object, const bool isExternal): symbolType(OBJECT), isExternal(isExternal), object(object), location(&object->location) {}

LgsSymbol::LgsSymbol(LgsInterface* interface): symbolType(INTERFACE), interface(interface), location(&interface->location) {}

LgsSymbol::LgsSymbol(LgsField* field): symbolType(FIELD), field(field), location(&field->location) {}

LgsSymbol::LgsSymbol(LgsEnum* lgsEnum, const bool isExternal): symbolType(ENUM), isExternal(isExternal), lgsEnum(lgsEnum), location(&lgsEnum->location) {}

LgsSymbol::LgsSymbol(LgsEnumField* enumField): symbolType(ENUM_FIELD), enumField(enumField), location(&enumField->location) {}

LgsSymbol::LgsSymbol(LgsFunc* func, const bool isExternal): symbolType(FUNC), isExternal(isExternal), func(func), location(&func->location) {}

LgsSymbol::LgsSymbol(LgsGroup* group): symbolType(GROUP), group(group), location(&group->location) {}

void* LgsSymbol::getSymbol() const {
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

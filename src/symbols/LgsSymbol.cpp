#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

class LgsTable;

LgsSymbol::LgsSymbol()
    : name(nullptr), symbolType(UNKNOWN), location(nullptr) {}

LgsSymbol::LgsSymbol(LgsParam* param)
    : name(&param->name), symbolType(PARAM), param(param), location(&param->location) {}

LgsSymbol::LgsSymbol(LgsField* field)
    : name(&field->name), symbolType(FIELD), field(field), location(&field->location) {}

LgsSymbol::LgsSymbol(LgsGroup* group)
    : name(&group->name), symbolType(GROUP), group(group), location(&group->location) {}

LgsSymbol::LgsSymbol(LgsInterface* interface)
    : name(&interface->name), symbolType(INTERFACE), interface(interface), location(&interface->location) {}

LgsSymbol::LgsSymbol(LgsSubType* subtype)
    : name(&subtype->name), symbolType(SUBTYPE), subtype(subtype), location(&subtype->location) {}

LgsSymbol::LgsSymbol(LgsObject* object, const bool isExternal, const bool isBuiltin)
    : name(&object->name), symbolType(OBJECT), isExternal(isExternal), isBuiltin(isBuiltin), object(object), location(&object->location) {}

LgsSymbol::LgsSymbol(LgsEnum* lgsEnum, const bool isExternal, const bool isBuiltin)
    : name(&lgsEnum->name), symbolType(ENUM), isExternal(isExternal), isBuiltin(isBuiltin), lgsEnum(lgsEnum), location(&lgsEnum->location) {}

LgsSymbol::LgsSymbol(LgsFunc* func, const bool isExternal, const bool isBuiltin)
    : name(&func->funcType->name), symbolType(FUNC), isExternal(isExternal), isBuiltin(isBuiltin), func(func), location(&func->location) {}

LgsSymbol::LgsSymbol(LgsVarDec* varDec)
    : name(&varDec->name), symbolType(VAR_DEC), varDec(varDec), location(&varDec->location) {}
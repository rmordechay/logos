#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsGeneric.h"
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

LgsSymbol::LgsSymbol(LgsInterface* interface)
    : name(&interface->name), symbolType(INTERFACE), interface(interface), location(&interface->location) {}

LgsSymbol::LgsSymbol(LgsSubType* subtype)
    : name(&subtype->name), symbolType(SUBTYPE), subtype(subtype), location(&subtype->location) {}

LgsSymbol::LgsSymbol(LgsGeneric* generic)
    : name(&generic->name), symbolType(GENERIC), generic(generic), location(&generic->location) {}

LgsSymbol::LgsSymbol(LgsObject* object, const bool isExternal, const bool isBuiltin)
    : name(&object->name), symbolType(OBJECT), isExternal(isExternal), isBuiltin(isBuiltin), object(object), location(&object->location) {}

LgsSymbol::LgsSymbol(LgsEnum* lgsEnum, const bool isExternal, const bool isBuiltin)
    : name(&lgsEnum->name), symbolType(ENUM), isExternal(isExternal), isBuiltin(isBuiltin), enum_(lgsEnum), location(&lgsEnum->location) {}

LgsSymbol::LgsSymbol(LgsFunc* func, const bool isExternal, const bool isBuiltin)
    : name(&func->funcType->name), symbolType(FUNC), isExternal(isExternal), isBuiltin(isBuiltin), func(func), location(&func->location) {}

LgsSymbol::LgsSymbol(LgsVarDec* varDec)
    : name(&varDec->name), symbolType(VAR_DEC), varDec(varDec), location(&varDec->location) {}

LgsType* LgsSymbol::getType() const {
    switch (symbolType) {
    case VAR_DEC:
        return varDec->type;
    case PARAM:
        return param->type;
    case FIELD:
        return field->type;
    case FUNC:
        return func->type;
    case OBJECT:
        return object;
    case INTERFACE:
        return interface;
    case SUBTYPE:
        return subtype;
    case GENERIC:
        return generic;
    case ENUM:
        return enum_;
    case UNKNOWN:
        break;
    }
    return nullptr;
}

LgsSymbol LgsSymbol::clone() const {
    switch (symbolType) {
    case VAR_DEC:
        return LgsSymbol(varDec->clone());
    case PARAM:
        return LgsSymbol(param);
    case FIELD:
        return LgsSymbol(field->clone());
    case FUNC:
        return LgsSymbol(func->cloneExpr());
    case OBJECT:
        return LgsSymbol(object->clone());
    case INTERFACE:
        return LgsSymbol(interface->clone());
    case SUBTYPE:
        return LgsSymbol(subtype->clone());
    case GENERIC:
        return LgsSymbol(generic->clone());
    case ENUM:
        return LgsSymbol(enum_->clone());
    case UNKNOWN:
        break;
    }
    assert(0);
}

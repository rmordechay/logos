#include "LgsSymbol.h"
#include "types/LgsEnum.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

class LgsTable;

LgsSymbol::LgsSymbol()
    : name(nullptr), symbolType(UNKNOWN), location(nullptr), unknown(nullptr) {
}

LgsSymbol::LgsSymbol(LgsParam* param)
    : name(&param->name), symbolType(PARAM), location(&param->location), param(param) {}

LgsSymbol::LgsSymbol(LgsField* field)
    : name(&field->name), symbolType(FIELD), location(&field->location), field(field) {}

LgsSymbol::LgsSymbol(LgsInterface* interface)
    : name(&interface->name), symbolType(INTERFACE), location(&interface->location), interface(interface) {}

LgsSymbol::LgsSymbol(LgsSubType* subtype, const bool isExternal)
    : name(&subtype->name), symbolType(SUBTYPE), location(&subtype->location), isExternal(isExternal), subtype(subtype) {}

LgsSymbol::LgsSymbol(LgsVarDec* varDec, const bool isBuiltin, const bool isExternal)
    : name(&varDec->name), symbolType(VAR_DEC), location(&varDec->location), isExternal(isExternal), isBuiltin(isBuiltin), varDec(varDec) {}

LgsSymbol::LgsSymbol(LgsObject* object, const bool isBuiltin, const bool isExternal)
    : name(&object->name), symbolType(OBJECT), location(&object->location), isExternal(isExternal), isBuiltin(isBuiltin), object(object) {}

LgsSymbol::LgsSymbol(LgsEnum* lgsEnum, const bool isBuiltin, const bool isExternal)
    : name(&lgsEnum->name), symbolType(ENUM), location(&lgsEnum->location), isExternal(isExternal), isBuiltin(isBuiltin), enum_(lgsEnum) {}

LgsSymbol::LgsSymbol(LgsFunc* func, const bool isBuiltin, const bool isExternal)
    : name(&func->funcType->name), symbolType(FUNC), location(&func->location), isExternal(isExternal), isBuiltin(isBuiltin), func(func) {}

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
        return LgsSymbol(varDec);
    case PARAM:
        return LgsSymbol(param);
    case FIELD:
        return LgsSymbol(field);
    case FUNC:
        return LgsSymbol(func);
    case OBJECT:
        return LgsSymbol(object);
    case INTERFACE:
        return LgsSymbol(interface);
    case SUBTYPE:
        return LgsSymbol(subtype);
    case ENUM:
        return LgsSymbol(enum_);
    case UNKNOWN:
        return LgsSymbol();
    }
    assert(0);
}

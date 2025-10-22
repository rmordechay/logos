#pragma once
#include "types/LgsGeneric.h"

class LgsType;
class LgsSubType;
class LgsVariable;
class LgsField;
class LgsEnum;
class LgsFunc;
class LgsInterface;
class LgsObject;
class LgsParam;
class LgsVarDec;
struct LgsLocation;

enum LgsSymbolType {
    VAR_DEC,
    PARAM,
    FIELD,
    FUNC,
    OBJECT,
    INTERFACE,
    SUBTYPE,
    GENERIC,
    ENUM,
    UNKNOWN,
};

struct LgsSymbol {
    std::string* name;
    LgsSymbolType symbolType;
    bool isExternal = false;
    bool isBuiltin = false;

    LgsVarDec* varDec = nullptr;
    LgsParam* param = nullptr;
    LgsObject* object = nullptr;
    LgsInterface* interface = nullptr;
    LgsSubType* subtype = nullptr;
    LgsGeneric* generic = nullptr;
    LgsField* field = nullptr;
    LgsEnum* enum_ = nullptr;
    LgsFunc* func = nullptr;
    LgsLocation* location;

    explicit LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsGeneric* generic);
    explicit LgsSymbol(LgsSubType* subtype);
    explicit LgsSymbol(LgsObject* object, bool isExternal = false, bool isBuiltin = false);
    explicit LgsSymbol(LgsEnum* lgsEnum, bool isExternal = false, bool isBuiltin = false);
    explicit LgsSymbol(LgsFunc* func, bool isExternal = false, bool isBuiltin = false);
    LgsType* getType() const;
};

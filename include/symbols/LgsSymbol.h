#pragma once
#include <string>

class LgsGeneric;
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
    LgsLocation* location;
    bool isExternal = false;
    bool isBuiltin = false;
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsInterface* interface;
        LgsSubType* subtype;
        LgsGeneric* generic;
        LgsField* field;
        LgsEnum* enum_;
        LgsFunc* func;
    };

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
    LgsSymbol clone() const;
};

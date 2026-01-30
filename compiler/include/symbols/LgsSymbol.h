#pragma once
#include <string>

class LgsGenericType;
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
    size_t refCount = 0;
    bool isExternal = false;
    bool isBuiltin = false;
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsInterface* interface;
        LgsSubType* subtype;
        LgsGenericType* generic;
        LgsField* field;
        LgsEnum* enum_;
        LgsFunc* func;
        void* unknown;
    };

    explicit LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsGenericType* generic);
    explicit LgsSymbol(LgsSubType* subtype, bool isExternal = false);
    explicit LgsSymbol(LgsVarDec* varDec, bool isBuiltin = false, bool isExternal = false);
    explicit LgsSymbol(LgsObject* object, bool isBuiltin = false, bool isExternal = false);
    explicit LgsSymbol(LgsEnum* lgsEnum, bool isBuiltin = false, bool isExternal = false);
    explicit LgsSymbol(LgsFunc* func, bool isBuiltin = false, bool isExternal = false);
    LgsType* getType() const;
    LgsSymbol clone() const;
};

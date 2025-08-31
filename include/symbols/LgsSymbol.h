#pragma once

class LgsVariable;
class LgsGroup;
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
    GROUP,
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
    LgsField* field = nullptr;
    LgsEnum* lgsEnum = nullptr;
    LgsFunc* func = nullptr;
    LgsGroup* group = nullptr;
    LgsLocation* location;

    explicit LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsGroup* group);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsObject* object, bool isExternal = false, bool isBuiltin = false);
    explicit LgsSymbol(LgsEnum* lgsEnum, bool isExternal = false, bool isBuiltin = false);
    explicit LgsSymbol(LgsFunc* func, bool isExternal = false, bool isBuiltin = false);
};

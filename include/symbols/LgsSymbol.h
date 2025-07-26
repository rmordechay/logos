#pragma once

class LgsInstance;
class LgsVariable;
class LgsGroup;
class LgsField;
class LgsEnum;
class LgsFunc;
class LgsInterface;
class LgsObject;
class LgsParam;
class LgsVarDec;
class Location;

enum LgsSymbolType {
    VAR_DEC,
    PARAM,
    FIELD,
    FUNC,
    OBJECT,
    SINGLETON,
    INTERFACE,
    GROUP,
    ENUM,
    UNKNOWN,
};

struct LgsSymbol {
    LgsSymbolType symbolType;
    bool isExternal = false;

    LgsVarDec* varDec = nullptr;
    LgsParam* param = nullptr;
    LgsObject* object = nullptr;
    LgsInstance* singleton = nullptr;
    LgsInterface* interface = nullptr;
    LgsField* field = nullptr;
    LgsEnum* lgsEnum = nullptr;
    LgsFunc* func = nullptr;
    LgsGroup* group = nullptr;
    Location* location;

    explicit LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsObject* object, bool isExternal = false);
    explicit LgsSymbol(LgsInstance* singleton);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsEnum* lgsEnum, bool isExternal = false);
    explicit LgsSymbol(LgsFunc* func, bool isExternal = false);
    explicit LgsSymbol(LgsGroup* group);
    void* getSymbol() const;
    ~LgsSymbol() = default;
};

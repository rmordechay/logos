#pragma once

class LgsGroup;
class LgsField;
class LgsEnum;
class LgsEnumField;
class LgsFunc;
class LgsInterface;
class LgsObject;
class LgsParam;
class LgsVarDec;
class Location;

enum LgsSymbolType {
    VAR_DEC,
    PARAM,
    ENUM_FIELD,
    FIELD,
    FUNC,
    OBJECT,
    INTERFACE,
    GROUP,
    ENUM,
    UNKNOWN,
};

struct LgsSymbol {
    LgsSymbolType symbolType;
    LgsVarDec* varDec = nullptr;
    LgsParam* param = nullptr;
    LgsObject* object = nullptr;
    LgsInterface* interface = nullptr;
    LgsField* field = nullptr;
    LgsEnum* lgsEnum = nullptr;
    LgsEnumField* enumField = nullptr;
    LgsFunc* func = nullptr;
    LgsGroup* group = nullptr;
    bool isExternal = false;

    explicit LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsObject* object, bool isExternal = false);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsField* field);
    explicit LgsSymbol(LgsEnum* lgsEnum, bool isExternal = false);
    explicit LgsSymbol(LgsEnumField* enumField);
    explicit LgsSymbol(LgsFunc* func, bool isExternal = false);
    explicit LgsSymbol(LgsGroup* group);
    Location* getLocation() const;
    void* getPtr() const;
    ~LgsSymbol() = default;
};



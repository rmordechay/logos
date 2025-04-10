#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

struct CodeGenMetadata;
class LgsEnum;
class LgsEnumField;
class LgsFunc;
class LgsInterface;
class LgsObject;
class LgsParam;
class LgsVarDec;

enum LgsSymbolType {
    VAR_DEC,
    PARAM,
    OBJECT,
    INTERFACE,
    FUNC,
    ENUM,
    ENUM_FIELD,
    UNKNOWN,
};

struct LgsSymbol {
    LgsSymbolType type;
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsInterface* interface;
        LgsFunc* func;
        LgsEnum* lgsEnum;
        LgsEnumField* enumField;
    };

    LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsFunc* func);
    explicit LgsSymbol(LgsObject* object);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsEnum* lgsEnum);
    LgsSymbol(LgsEnumField* enumField);
    void free(CodeGenMetadata* metadata) const;
    ~LgsSymbol() = default;
};

#endif //LOGOSSYMBOL_H

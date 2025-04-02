#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

struct CodeGenMetadata;
class LgsEnum;
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
    };

    LgsSymbol();
    explicit LgsSymbol(LgsParam* param);
    explicit LgsSymbol(LgsVarDec* varDec);
    explicit LgsSymbol(LgsFunc* func);
    explicit LgsSymbol(LgsObject* object);
    explicit LgsSymbol(LgsInterface* interface);
    explicit LgsSymbol(LgsEnum* lgsEnum);
    void free(CodeGenMetadata* metadata) const;
};

#endif //LOGOSSYMBOL_H

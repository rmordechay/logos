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
    bool isReturnValue = false;
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsInterface* interface;
        LgsFunc* func;
        LgsEnum* lgsEnum;
    };

    LgsSymbol();
    LgsSymbol(LgsSymbolType type, LgsParam* param);
    LgsSymbol(LgsSymbolType type, LgsVarDec* varDec);
    LgsSymbol(LgsSymbolType type, LgsFunc* funcImpl);
    LgsSymbol(LgsSymbolType type, LgsObject* object);
    LgsSymbol(LgsSymbolType type, LgsInterface* interface);
    LgsSymbol(LgsSymbolType type, LgsEnum* lgsEnum);
    void free(CodeGenMetadata* metadata) const;
};

#endif //LOGOSSYMBOL_H

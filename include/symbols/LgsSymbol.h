#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

class LgsParam;
class LgsVarDec;
class LgsMethodImpl;
class LgsFuncImpl;
class LgsExpr;
class LgsArrayIndex;
class LgsArray;
class LgsSelection;
class LgsBinaryExpr;
class LgsConst;
class LgsVariable;
class LgsFuncCall;
class LgsInstance;
class LgsFunc;
class LgsField;
class LgsObject;

enum LgsSymbolType {
    VAR_DEC,
    PARAM,
    OBJECT,
    FUNC,
};

struct LgsSymbol {
    LgsSymbolType type;
    union {
        LgsObject* object;
        LgsVarDec* varDec;
        LgsParam* param;
        LgsFunc* func;
    };

    LgsSymbol() :
        type(static_cast<LgsSymbolType>(0)),
        object(nullptr) {
    }

    LgsSymbol(const LgsSymbolType type, LgsParam* param) :
        type(type),
        param(param) {
    }

    LgsSymbol(const LgsSymbolType type, LgsVarDec* varDec) :
        type(type),
        varDec(varDec) {
    }

    LgsSymbol(const LgsSymbolType type, LgsFunc* funcImpl) :
        type(type),
        func(funcImpl) {
    }

    LgsSymbol(const LgsSymbolType type, LgsObject* object) :
        type(type),
        object(object) {
    }
};

#endif //LOGOSSYMBOL_H

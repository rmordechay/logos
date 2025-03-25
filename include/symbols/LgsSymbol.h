#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

using namespace std;

class LgsEnum;
class LgsParam;
class LgsVarDec;
class LgsMethodImpl;
class LgsFuncImpl;
class LgsExpr;
class LgsArrayIndex;
class LgsArray;
class LgsSelection;
class LgsBinaryExpr;
class LgsConstExpr;
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
    ENUM,
};

struct LgsSymbol {
    LgsSymbolType type;
    union {
        LgsObject* object;
        LgsVarDec* varDec;
        LgsParam* param;
        LgsFunc* func;
        LgsEnum* lgsEnum;
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

    LgsSymbol(const LgsSymbolType type, LgsEnum* lgsEnum) :
        type(type),
        lgsEnum(lgsEnum) {
    }
};

#endif //LOGOSSYMBOL_H

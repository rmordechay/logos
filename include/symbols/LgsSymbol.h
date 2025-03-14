#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

class LgsParam;
class LgsBuiltinFunc;
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
    BUILTIN_FUNC,
    FUNC_IMPL,
    SELECTION,
};

struct LgsSymbol {
    LgsSymbolType type;
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsBuiltinFunc* builtinFunc;
        LgsFuncImpl* funcImpl;
        LgsSelection* selection;
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

    LgsSymbol(const LgsSymbolType type, LgsSelection* selection) :
        type(type),
        selection(selection) {
    }

    LgsSymbol(const LgsSymbolType type, LgsBuiltinFunc* builtinFunc) :
        type(type),
        builtinFunc(builtinFunc) {
    }

    LgsSymbol(const LgsSymbolType type, LgsFuncImpl* funcImpl) :
        type(type),
        funcImpl(funcImpl) {
    }

    LgsSymbol(const LgsSymbolType type, LgsObject* object) :
        type(type),
        object(object) {
    }
};

#endif //LOGOSSYMBOL_H

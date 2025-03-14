#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H


class LgsParam;
class LgsLoopVar;
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
    LOOP_VAR,
    OBJECT,
    FIELD,
    BUILTIN_FUNC,
    FUNC_IMPL,
    METHOD_IMPL,
    SELECTION,
};

struct LgsSymbol {
    LgsSymbolType type;
    union {
        LgsVarDec* varDec;
        LgsParam* param;
        LgsObject* object;
        LgsField* field;
        LgsLoopVar* loopVar;
        LgsBuiltinFunc* builtinFunc;
        LgsFuncImpl* funcImpl;
        LgsMethodImpl* methodImpl;
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

    LgsSymbol(const LgsSymbolType type, LgsField* field) :
        type(type),
        field(field) {
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

    LgsSymbol(const LgsSymbolType type, LgsMethodImpl* methodImpl) :
        type(type),
        methodImpl(methodImpl) {
    }

    LgsSymbol(const LgsSymbolType type, LgsLoopVar* loopVar) :
        type(type),
        loopVar(loopVar) {
    }

};


#endif //LOGOSSYMBOL_H

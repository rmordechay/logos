#ifndef LOGOSOBJECT_H
#define LOGOSOBJECT_H
#include "exprs/LogosUnaryExpr.h"
#include "funcs/LogosFunc.h"
#include "stmts/LogosVarDec.h"
#include "types/LogosUserType.h"

class LogosObject final : public LogosUnaryExpr {
public:
    vector<LogosVarDec*> fields;
    vector<LogosFunc*> funcs;
    LogosUserType* type = nullptr;
    explicit LogosObject(LogosUserType* type) : type(type) {}

    ~LogosObject() override {
        delete type;
        for (const auto var : fields) {
            delete var;
        }
        for (const auto func : funcs) {
            delete func;
        }
    }
};

#endif //LOGOSOBJECT_H

#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include <LogosMetadata.h>
#include "unary/LogosUnaryExpr.h"
#include <variant>

class LgsStringConst;
using namespace std;

class LgsConstant final : public LgsUnaryExpr {
public:
    variant<int, LgsStringConst*, float, bool> value;

    LgsConstant(LgsType* type, int intVal) : LgsUnaryExpr(type), value(intVal) {}
    LgsConstant(LgsType* type, LgsStringConst* stringVal) : LgsUnaryExpr(type), value(stringVal) {}
    LgsConstant(LgsType* type, float floatVal) : LgsUnaryExpr(type), value(floatVal) {}
    LgsConstant(LgsType* type, bool boolVal) : LgsUnaryExpr(type), value(boolVal) {}

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsConstant() override = default;
};


#endif //LOGOSCONSTANTEXPR_H

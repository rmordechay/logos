#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include <LogosMetadata.h>
#include "LogosUnaryExpr.h"
#include <variant>

class LogosStringConst;
using namespace std;

class LogosConstant final : public LogosUnaryExpr {
public:
    variant<int, LogosStringConst*, float, bool> value;

    LogosConstant(LogosType* type, int intVal) : LogosUnaryExpr(type), value(intVal) {}
    LogosConstant(LogosType* type, LogosStringConst* stringVal) : LogosUnaryExpr(type), value(stringVal) {}
    LogosConstant(LogosType* type, float floatVal) : LogosUnaryExpr(type), value(floatVal) {}
    LogosConstant(LogosType* type, bool boolVal) : LogosUnaryExpr(type), value(boolVal) {}

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosConstant() override = default;
};


#endif //LOGOSCONSTANTEXPR_H

#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include <LogosMetadata.h>
#include <LogosSymbol.h>
#include "LogosUnaryExpr.h"

using namespace std;

class LogosConstant final : public LogosUnaryExpr {
public:
    union {
        int intVal;
        string stringVal;
        float floatVal;
        bool boolVal;
    };

    LogosConstant(LogosType* type, int intVal) : LogosUnaryExpr(type), intVal(intVal) {}
    LogosConstant(LogosType* type, const string& stringVal) : LogosUnaryExpr(type), stringVal(stringVal) {}
    LogosConstant(LogosType* type, float floatVal) : LogosUnaryExpr(type), floatVal(floatVal) {}
    LogosConstant(LogosType* type, bool boolVal) : LogosUnaryExpr(type), boolVal(boolVal) {}

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    void setName(string name) override;
    string getName() override;
    LogosSymbolType getSymbolType() override;
    ~LogosConstant() override;
};


#endif //LOGOSCONSTANTEXPR_H

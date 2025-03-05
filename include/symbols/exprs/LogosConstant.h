#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include <LogosMetadata.h>
#include <LogosSymbol.h>
#include "LogosUnaryExpr.h"
#include <variant>

using namespace std;

class LogosConstant final : public LogosUnaryExpr {
public:
    std::variant<int, string, float, bool> value;

    LogosConstant(LogosType* type, int intVal) : LogosUnaryExpr(type), value(intVal) {}
    LogosConstant(LogosType* type, const string& stringVal) : LogosUnaryExpr(type), value(stringVal) {}
    LogosConstant(LogosType* type, float floatVal) : LogosUnaryExpr(type), value(floatVal) {}
    LogosConstant(LogosType* type, bool boolVal) : LogosUnaryExpr(type), value(boolVal) {}

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    void setName(string name) override;
    string getName() override;
    LogosSymbolType getSymbolType() override;
    ~LogosConstant() override = default;
};


#endif //LOGOSCONSTANTEXPR_H

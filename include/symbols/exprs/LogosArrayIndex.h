#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LogosUnaryExpr.h"

#include <LogosValue.h>


class LogosArrayIndex final : public LogosUnaryExpr {
public:
    LogosUnaryExpr* baseExpr;
    vector<LogosExpr*> exprs;

    explicit LogosArrayIndex(LogosUnaryExpr* baseExpr) : baseExpr(baseExpr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    LogosSymbolType getSymbolType() override;
    void setName(string name) override;
    string getName() override;
    ~LogosArrayIndex() override = default;
};



#endif //LOGOSARRAYINDEX_H

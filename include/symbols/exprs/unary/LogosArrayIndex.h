#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LogosUnaryExpr.h"

#include <LogosValue.h>


class LogosArrayIndex final : public LogosUnaryExpr {
public:
    LogosUnaryExpr* baseExpr;
    vector<LogosExpr*> indexExprs;

    explicit LogosArrayIndex(LogosUnaryExpr* baseExpr, const vector<LogosExpr*>& indexExprs) : baseExpr(baseExpr), indexExprs(indexExprs) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LogosArrayIndex() override;
};

#endif //LOGOSARRAYINDEX_H

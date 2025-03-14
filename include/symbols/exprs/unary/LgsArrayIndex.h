#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LogosUnaryExpr.h"

#include <LgsValue.h>


class LgsArrayIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    vector<LogosExpr*> indexExprs;

    explicit LgsArrayIndex(LgsUnaryExpr* baseExpr, const vector<LogosExpr*>& indexExprs) : baseExpr(baseExpr), indexExprs(indexExprs) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsArrayIndex() override;
};

#endif //LOGOSARRAYINDEX_H

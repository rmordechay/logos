#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LgsUnaryExpr.h"

#include <LgsValue.h>


class LgsArrayIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    vector<LgsExpr*> indexExprs;

    explicit LgsArrayIndex(LgsUnaryExpr* baseExpr, const vector<LgsExpr*>& indexExprs) : baseExpr(baseExpr), indexExprs(indexExprs) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    LgsExpr* lastExpr() const;
    ~LgsArrayIndex() override;
};

#endif //LOGOSARRAYINDEX_H

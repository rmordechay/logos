#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LgsUnaryExpr.h"

#include <LgsValue.h>


class LgsArrayIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    vector<LgsExpr*> indices;

    explicit LgsArrayIndex(LgsUnaryExpr* baseExpr, const vector<LgsExpr*>& indices) : baseExpr(baseExpr), indices(indices) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* getGEP(CodeGenMetadata* metadata) const;
    string getName() override;
    ~LgsArrayIndex() override;
};

#endif //LOGOSARRAYINDEX_H

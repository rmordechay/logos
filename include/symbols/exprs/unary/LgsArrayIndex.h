#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LgsUnaryExpr.h"

#include <LgsValue.h>


class LgsArrayIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* expr;
    LgsExpr* index;

    explicit LgsArrayIndex(LgsUnaryExpr* baseExpr, LgsExpr* index) : expr(baseExpr), index(index) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsArrayIndex() override;
};

#endif //LOGOSARRAYINDEX_H

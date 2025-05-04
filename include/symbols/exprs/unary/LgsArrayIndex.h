#ifndef LOGOSARRAYINDEX_H
#define LOGOSARRAYINDEX_H
#include "LgsUnaryExpr.h"
#include <LgsValue.h>

class LgsIndex final {
public:
    LgsExpr* from;
    LgsExpr* to;

    explicit LgsIndex(LgsExpr* from, LgsExpr* to = nullptr) : from(from), to(to) {}
    ~LgsIndex() = default;
};

class LgsArrayIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    vector<LgsIndex*> indices;

    explicit LgsArrayIndex(LgsUnaryExpr* baseExpr, const vector<LgsIndex*>& indices) : baseExpr(baseExpr), indices(indices) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* getGEP(CodeGenMetadata* metadata) const;
    string getName() override;
    string getNameWithTypes();
    ~LgsArrayIndex() override;
};

#endif //LOGOSARRAYINDEX_H

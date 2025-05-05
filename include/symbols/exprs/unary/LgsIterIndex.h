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

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    vector<LgsIndex*> indices;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, const vector<LgsIndex*>& indices) : baseExpr(baseExpr), indices(indices) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void assignIRValue(CodeGenMetadata* metadata, LgsExpr* value) const;
    Value* getGEP(CodeGenMetadata* metadata) const;
    string getName() override;
    string getNameWithTypes();
    ~LgsIterIndex() override;
};

#endif //LOGOSARRAYINDEX_H

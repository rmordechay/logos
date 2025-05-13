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
    string getNameWithTypes();
    Value* getGEP(CodeGenMetadata* metadata) const;
    Value* createIRValueFromMap(CodeGenMetadata* metadata, LgsMap* map) const;
    Value* createIRValueFromArray(CodeGenMetadata* metadata, LgsArray* arr) const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void assignIRValue(CodeGenMetadata* metadata, LgsExpr* value) const;
    string getName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

#endif //LOGOSARRAYINDEX_H

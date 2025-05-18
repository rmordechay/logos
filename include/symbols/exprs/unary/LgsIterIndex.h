#ifndef LOGOSITERINDEX_H
#define LOGOSITERINDEX_H
#include "LgsUnaryExpr.h"
#include <LgsValue.h>

class LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    vector<LgsIndex*> indices;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, const vector<LgsIndex*>& indices = {}) : baseExpr(baseExpr), indices(indices) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* getGEP(CodeGenMetadata* metadata) const;
    Value* createIRDynArray(CodeGenMetadata* metadata, LgsArray* arr) const;
    Value* createMapIRValue(CodeGenMetadata* metadata, LgsMap* map) const;
    Value* createStrIRValue(CodeGenMetadata* metadata) const;
    void storeHashMap(CodeGenMetadata* metadata, LgsHashMap* hashMap) const;
    void storeScalar(CodeGenMetadata* metadata, LgsExpr* value);
    void storeArray(CodeGenMetadata* metadata, const LgsArrayExpr* arr) const;
    void castExpr(LgsType* other) override;
    Value* getLength(CodeGenMetadata* metadata) override;
    string getName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

class LgsIndex final {
public:
    LgsExpr* from;
    LgsExpr* to;

    explicit LgsIndex(LgsExpr* from, LgsExpr* to = nullptr) : from(from), to(to) {}
    ~LgsIndex() = default;
};

#endif //LOGOSITERINDEX_H

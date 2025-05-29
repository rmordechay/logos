#ifndef LOGOSITERINDEX_H
#define LOGOSITERINDEX_H
#include "LgsUnaryExpr.h"
#include <LgsValue.h>

struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* getGEP(CodeGenMetadata* metadata) const;
    Value* getIRFromDynArray(CodeGenMetadata* metadata, LgsArray* arr) const;
    Value* getIRFromMap(CodeGenMetadata* metadata, LgsMap* map) const;
    Value* getIRFromStr(CodeGenMetadata* metadata) const;
    void storeHashMap(CodeGenMetadata* metadata, LgsHashMap* hashMap) const;
    void storeScalar(CodeGenMetadata* metadata, LgsExpr* value);
    void storeArray(CodeGenMetadata* metadata, const LgsArrayExpr* arr) const;
    Value* getLength(CodeGenMetadata* metadata) override;
    string getName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};

#endif //LOGOSITERINDEX_H

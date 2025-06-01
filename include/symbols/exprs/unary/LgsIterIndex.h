#ifndef LOGOSITERINDEX_H
#define LOGOSITERINDEX_H
#include "LgsUnaryExpr.h"
#include <LgsValue.h>

class LgsMap;
class LgsArray;
struct LgsIndex;

class LgsIterIndex final : public LgsUnaryExpr {
public:
    LgsUnaryExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsUnaryExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* getGEP(CodegenMetadata* metadata) const;
    Value* getIRFromDynArray(CodegenMetadata* metadata, LgsArray* arr) const;
    Value* getIRFromMap(CodegenMetadata* metadata, LgsMap* map) const;
    Value* getIRFromStr(CodegenMetadata* metadata) const;
    void storeHashMap(CodegenMetadata* metadata, LgsHashMap* hashMap) const;
    void storeScalar(CodegenMetadata* metadata, LgsExpr* value);
    void storeArray(CodegenMetadata* metadata, const LgsArrayExpr* arr) const;
    Value* getLength(CodegenMetadata* metadata) override;
    string getName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};

#endif //LOGOSITERINDEX_H

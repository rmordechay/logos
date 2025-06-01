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
    Value* createIRValue(Module* module) override;
    Value* getGEP(Module* module) const;
    Value* getIRFromDynArray(Module* module, LgsArray* arr) const;
    Value* getIRFromMap(Module* module, LgsMap* map) const;
    Value* getIRFromStr(Module* module) const;
    void storeHashMap(Module* module, LgsHashMap* hashMap) const;
    void storeScalar(Module* module, LgsExpr* value);
    void storeArray(Module* module, const LgsArrayExpr* arr) const;
    Value* getLength(Module* module) override;
    string getName() override;
    string prettyName() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;
};

#endif //LOGOSITERINDEX_H

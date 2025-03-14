#ifndef SELECTION_H
#define SELECTION_H
#include "types/LgsObject.h"

class LgsUnaryExpr;
class LgsMethodCall;

class LgsSelection final : public LgsUnaryExpr {
public:
    vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* resolveType(CodeGenMetadata* metadata, LgsUnaryExpr* nextExpr, LgsType* logosType) const;
    Value* resolveSelectionVariable(CodeGenMetadata* metadata, const LgsVariable* variable, LgsUnaryExpr* nextExpr) const;
    LogosExpr* lastExpr() const;
    string getName() override;
    ~LgsSelection() override;
};

#endif //SELECTION_H

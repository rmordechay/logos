#ifndef SELECTION_H
#define SELECTION_H
#include "types/LgsObject.h"

class LgsUnaryExpr;

class LgsSelection final : public LgsUnaryExpr {
public:
    vector<LgsUnaryExpr*> exprs;

    explicit LgsSelection(const vector<LgsUnaryExpr*>& exprs) : exprs(exprs) {}
    string getName() override;
    LgsExpr* lastExpr() const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsExpr* resolveSelection(CodeGenMetadata* metadata) const;
    ~LgsSelection() override;
};

#endif //SELECTION_H

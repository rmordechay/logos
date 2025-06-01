#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LgsStmt.h"
#include "exprs/unary/LgsSelection.h"

class LgsExpr;
class LgsType;

class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* lValue;
    LgsExpr* rValue;

    void createIRStmt(Module* module) override;
    void assignIRIterIndex(Module* module, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void assignIRSelection(Module* module, const LgsSelection* selection, LgsExpr* expr) const;
    ~LgsAssignment() override;
};

#endif //LOGOSFIELDDEC_H

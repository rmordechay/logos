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

    void createIRStmt(CodegenMetadata* metadata) override;
    void assignIRIterIndex(CodegenMetadata* metadata, LgsIterIndex* iterIndex, LgsExpr* value) const;
    void assignIRSelection(CodegenMetadata* metadata, const LgsSelection* selection, LgsExpr* expr) const;
    ~LgsAssignment() override;
};

#endif //LOGOSFIELDDEC_H

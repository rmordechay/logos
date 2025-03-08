#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LogosStmt.h"

class LogosExpr;
class LogosType;

class LogosAssignment final : public LogosStmt {
public:
    LogosExpr* lvalue;
    LogosExpr* rvalue;

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosAssignment() override;
};

#endif //LOGOSFIELDDEC_H

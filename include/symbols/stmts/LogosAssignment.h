#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LogosStmt.h"

class LogosExpr;
class LogosType;

class LogosAssignment final : public LogosStmt {
public:
    vector<string> names;
    LogosField* field = nullptr;
    LogosExpr* expr = nullptr;

    explicit LogosAssignment(LogosExpr* expr) : expr(expr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosAssignment() override;
};

#endif //LOGOSFIELDDEC_H

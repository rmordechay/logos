#ifndef LOGOSFIELDDEC_H
#define LOGOSFIELDDEC_H
#include "LogosStmt.h"

class LogosExpr;
class LogosType;

class LogosFieldDef final : public LogosStmt {
public:
    int position = -1;
    vector<string> names;
    LogosExpr* expr = nullptr;

    LogosFieldDef(const vector<string>& names, LogosExpr* expr) : names(names), expr(expr) {}
    Value* computeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosFieldDef() override;
};

#endif //LOGOSFIELDDEC_H

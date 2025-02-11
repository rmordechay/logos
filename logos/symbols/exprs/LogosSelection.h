#ifndef SELECTION_H
#define SELECTION_H
#include "LogosExpr.h"
#include "LogosUnaryExpr.h"

class LogosSelection final : public LogosExpr {
public:
    const vector<string> names;

    explicit LogosSelection(const vector<string>& names) : LogosExpr(nullptr), names(names) {}
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosSelection() override = default;
};


#endif //SELECTION_H

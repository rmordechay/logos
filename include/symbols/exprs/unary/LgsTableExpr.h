#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsTable.h"

class LgsTableExpr final : public LgsUnaryExpr {
public:
    LgsTable* tableType;

    explicit LgsTableExpr(LgsTable* tableType = new LgsTable()): tableType(tableType) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    std::string pname() override;
    ~LgsTableExpr() override;
};

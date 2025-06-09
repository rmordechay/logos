#pragma once
#include "LgsConstExpr.h"
#include "LgsIntConst.h"



class LgsStrConst final : public LgsConstExpr {
public:
    LgsStr strType;
    string value;
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : LgsConstExpr(&strType), value(value) {
        strType.isStatic = true;
        strType.sizeExpr = new LgsIntConst(value.size());
    }

    Value* createIRValue(LgsRuntime* runtime) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};



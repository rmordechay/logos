#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConstExpr.h"
#include "LgsIntConst.h"
#include "types/LgsStr.h"
#include <string>

class LgsStrConst final : public LgsConstExpr {
public:
    LgsStr strType;
    string value;
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : LgsConstExpr(&strType), value(value) {
        strType.isStatic = true;
        strType.sizeExpr = new LgsIntConst(value.size());
    }
    Value* getLength(Module* module) override;
    Value* createIRValue(Module* module) override;
    Value* eqIR(Module* module, LgsExpr* other) override;
    Value* addIR(Module* module, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H

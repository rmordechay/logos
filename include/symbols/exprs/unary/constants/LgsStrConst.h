#ifndef LOGOSSTRINGCONST_H
#define LOGOSSTRINGCONST_H
#include "LgsConstExpr.h"
#include "types/str/LgsStr.h"
#include <string>

class LgsStrConst final : public LgsConstExpr {
public:
    LgsStr strType;
    string value;
    vector<LgsExpr*> templateParts;

    explicit LgsStrConst(const string& value) : LgsConstExpr(&strType), value(value) {
        strType.isStatic = true;
    }

    string getStrFormatPart() const override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* eqIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsStrConst() override = default;
};

#endif //LOGOSSTRINGCONST_H

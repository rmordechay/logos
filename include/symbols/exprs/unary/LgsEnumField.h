#ifndef LGSENUMFIELD_H
#define LGSENUMFIELD_H
#include "LgsUnaryExpr.h"
#include "stmts/LgsField.h"

class LgsEnumField final : public LgsField {
public:
    string text;

    LgsEnumField(const string& name, const size_t position, const string& text) : LgsField(name, position, nullptr, nullptr), text(text){}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsEnumField() override = default;
};

#endif //LGSENUMFIELD_H

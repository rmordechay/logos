#ifndef LGSENUMFIELD_H
#define LGSENUMFIELD_H
#include "LgsUnaryExpr.h"

class LgsEnumField final : public LgsUnaryExpr {
public:
    size_t position;
    string name;
    string text;

    LgsEnumField(const size_t position, const string& name, const string& text) : position(position), name(name), text(text) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsEnumField() override = default;
};

#endif //LGSENUMFIELD_H

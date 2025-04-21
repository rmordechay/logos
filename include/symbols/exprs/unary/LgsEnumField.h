#ifndef LGSENUMFIELD_H
#define LGSENUMFIELD_H
#include "stmts/LgsField.h"

class LgsEnumField final : public LgsField {
public:
    string text;
    LgsEnum* parent;

    LgsEnumField(LgsEnum* parent, const string& name, const size_t position, const string& text) : LgsField(name, position, nullptr, nullptr), text(text), parent(parent){}
    Value* getIRValue(CodeGenMetadata* metadata) override;
    ~LgsEnumField() override = default;
};

#endif //LGSENUMFIELD_H

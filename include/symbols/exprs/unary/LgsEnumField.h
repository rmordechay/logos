#ifndef LGSENUMFIELD_H
#define LGSENUMFIELD_H
#include "stmts/LgsField.h"

class LgsEnumField final : public LgsField {
public:
    string text;
    LgsEnum* parent;

    LgsEnumField(LgsEnum* parent, const string& name, const string& text) : LgsField(name, nullptr, nullptr), text(text), parent(parent){}
    Value* getGEP(CodegenMetadata* metadata, Value* instance = nullptr) override;
    ~LgsEnumField() override = default;
};

#endif //LGSENUMFIELD_H

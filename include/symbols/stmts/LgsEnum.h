#ifndef LGSENUM_H
#define LGSENUM_H
#include "LgsStmt.h"

class EnumField final : public LgsValue {
public:
    size_t position;
    string name;
    string text;

    EnumField(size_t position, const string& name, const string& text) : position(position), name(name), text(text) {}
    ~EnumField() override = default;
};

class LgsEnum final : public LgsStmt {
public:
    vector<EnumField> fields;

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsEnum() override = default;
};

#endif //LGSENUM_H

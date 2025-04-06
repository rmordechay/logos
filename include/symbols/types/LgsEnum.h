#ifndef LGSENUM_H
#define LGSENUM_H
#include "LgsType.h"

class EnumField final : public LgsValue {
public:
    size_t position;
    string name;
    string text;

    EnumField(size_t position, const string& name, const string& text) : position(position), name(name), text(text) {}
    ~EnumField() override = default;
};

class LgsEnum final : public LgsType {
public:
    string name;
    vector<EnumField> enums;

    explicit LgsEnum(const string& name) : name(name) {}
    const string getName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsEnum() override = default;
};

#endif //LGSENUM_H

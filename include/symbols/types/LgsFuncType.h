#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"

enum LgsFuncOpts : uint16_t {
    METHOD = 1 << 0,
    STATIC = 1 << 1,
    PUBLIC = 1 << 2,
    VIRTUAL = 1 << 3,
    VARIADIC = 1 << 4,
    ANONYMOUS = 1 << 5,
    SWAP_RETURN = 1 << 6,
    HAS_DEFAULTS = 1 << 7,
};

class LgsFuncType final : public LgsType {
public:
    string name;
    string IRName;
    string parentName;
    LgsType* rt = nullptr;
    vector<LgsParam> params;
    uint16_t flags = 0;
    int returnParamIndex = -1;
    FunctionType* IRType = nullptr;

    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsType* clone() override;
    bool hasFlag(LgsFuncOpts f) const;
    void setFlag(LgsFuncOpts f);
    ~LgsFuncType() override = default;
};

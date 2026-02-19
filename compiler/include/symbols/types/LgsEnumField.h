#pragma once
#include "LgsEnum.h"

class LgsEnumField final : public LgsEnum {
public:
    size_t index;
    std::string fieldName;

    LgsEnumField(const std::string& enumName, const std::string& fieldName, const size_t index): LgsEnum(enumName), index(index), fieldName(fieldName) {}
    std::string getName() override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    bool canCastTo(LgsType* other) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
};

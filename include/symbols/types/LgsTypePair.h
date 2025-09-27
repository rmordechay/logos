#pragma once
#include "LgsType.h"

class LgsTypePair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;
    StructType* pairIRType = nullptr;

    explicit LgsTypePair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    Lgs_RTType getRTType() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    std::string getName() override;
    std::string pname() override;
    json::value asJsonStr() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};

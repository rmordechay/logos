#pragma once
#include "funcs/LgsFunc.h"
#include "types/primitives/LgsInt.h"
#include "LgsIterable.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";

    explicit LgsSArray(LgsType* baseType = nullptr): LgsIterable(baseType) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    Value* IRLength(LgsLLVMGen& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    json::value asJSON() override;
};

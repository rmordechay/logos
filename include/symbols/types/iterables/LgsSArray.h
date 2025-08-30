#pragma once
#include "funcs/LgsFunc.h"
#include "../primitives/LgsInt.h"
#include "LgsIterable.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";
    LgsFunc* lenFunc = new LgsFunc("len", &LGS_INT, {this}, PUBLIC | METHOD);

    explicit LgsSArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        isSliceable = true;
        addMethod(lenFunc);
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    Value* IRLength(LgsLLVMGen& cg, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
    ~LgsSArray() override;
};

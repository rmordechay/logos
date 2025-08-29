#pragma once
#include "funcs/LgsFunc.h"
#include "codegen/LgsCodeGen.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsLong.h"
#include "types/LgsIterable.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsFunc* lenFunc = new LgsFunc("len", &LGS_LONG, {this}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* isEmptyFunc = new LgsFunc("isEmpty", &LGS_BOOL, {this}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* isNotEmptyFunc = new LgsFunc("isNotEmpty", &LGS_BOOL, {this}, INTERNAL | PUBLIC | METHOD);

    LgsStr();
    Type* getIRBaseType(LgsLLVMGen* cg) const;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    std::string strFormatPart() const override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsLLVMGen& cg, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
};

#pragma once
#include "funcs/LgsFunc.h"
#include "codegen/LgsCodeGenVisitor.h"
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

    LgsStr() : LgsIterable(&LGS_CHAR) {
        lenFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) {
            return codeGen.callStrLen(args[0]->IRValue);
        };
        isEmptyFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) {
            const auto strLen = codeGen.callStrLen(args[0]->IRValue);
            return codeGen.builder.CreateICmpEQ(strLen, codeGen.builder.getInt64(0));
        };
        isNotEmptyFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) {
            const auto strLen = codeGen.callStrLen(args[0]->IRValue);
            return codeGen.builder.CreateICmpNE(strLen, codeGen.builder.getInt64(0));
        };
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
        isSliceable = true;
    }
    Type* getIRBaseType(LgsCodeGen* codeGen) const;
    Type* getIRType(LgsCodeGen& codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    std::string strFormatPart() const override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsCodeGen& codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
};

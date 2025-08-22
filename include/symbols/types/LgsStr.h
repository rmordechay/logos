#pragma once
#include "funcs/LgsFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsLong.h"
#include "types/LgsIterable.h"

class LgsStrLen final : public LgsFunc {
public:
    static constexpr auto name = "len";
    explicit LgsStrLen(LgsType* parent): LgsFunc(name, &LGS_LONG, {parent}, INTERNAL | PUBLIC | METHOD) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        return codeGen->callStrLen(args[0]->getIRValue(codeGen));
    }
};

class LgsStrIsEmpty final : public LgsFunc {
public:
    static constexpr auto name = "isEmpty";
    explicit LgsStrIsEmpty(LgsType* parent): LgsFunc(name, &LGS_BOOL, {parent}, INTERNAL | PUBLIC | METHOD) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        const auto strLen = codeGen->callStrLen(args[0]->getIRValue(codeGen));
        return codeGen->builder.CreateICmpEQ(strLen, codeGen->builder.getInt64(0));
    }
};

class LgsStrIsNotEmpty final : public LgsFunc {
public:
    static constexpr auto name = "isNotEmpty";
    explicit LgsStrIsNotEmpty(LgsType* parent): LgsFunc(name, &LGS_BOOL, {parent}, INTERNAL | PUBLIC | METHOD) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        const auto strLen = codeGen->callStrLen(args[0]->getIRValue(codeGen));
        return codeGen->builder.CreateICmpNE(strLen, codeGen->builder.getInt64(0));
    }
};

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrLen* lenFunc = new LgsStrLen(this);
    LgsStrIsEmpty* isEmptyFunc = new LgsStrIsEmpty(this);
    LgsStrIsNotEmpty* isNotEmptyFunc = new LgsStrIsNotEmpty(this);

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
        isSliceable = true;
    }
    Type* getIRBaseType(LgsCodeGen* codeGen) const;
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    std::string strFormatPart() const override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
};

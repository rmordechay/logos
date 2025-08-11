#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsLong.h"
#include "types/LgsIterable.h"

class LgsStrLen final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "len";
    explicit LgsStrLen(LgsType* parent): LgsBuiltinFunc(name, &LGS_LONG, parent->getName(), {parent}, true) {}
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->callStrLen(args[0]->getIRValue(codeGen));
    }
    ~LgsStrLen() override = default;
};

class LgsStrIsEmpty final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "isEmpty";
    explicit LgsStrIsEmpty(LgsType* parent): LgsBuiltinFunc(name, &LGS_BOOL, parent->getName(), {parent}, true) {}
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        const auto strLen = codeGen->callStrLen(args[0]->getIRValue(codeGen));
        return codeGen->builder.CreateICmpEQ(strLen, codeGen->builder.getInt64(0));
    }
    ~LgsStrIsEmpty() override = default;
};

class LgsStrIsNotEmpty final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "isNotEmpty";
    explicit LgsStrIsNotEmpty(LgsType* parent): LgsBuiltinFunc(name, &LGS_BOOL, parent->getName(), {parent}, true) {}
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        const auto strLen = codeGen->callStrLen(args[0]->getIRValue(codeGen));
        return codeGen->builder.CreateICmpNE(strLen, codeGen->builder.getInt64(0));
    }
    ~LgsStrIsNotEmpty() override = default;
};

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    size_t initialLength = 0;
    LgsStrLen lenFunc{this};
    LgsStrIsEmpty isEmptyFunc{this};
    LgsStrIsNotEmpty isNotEmptyFunc{this};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
        unpackLength = 1;
        canSlice = true;
    }
    Type* getIRBaseType(LgsCodeGen* codeGen) const;
    size_t getSizeBytes() override;
    string getName() override;
    string prettyName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    LgsType* getIndexType() override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsStr() override = default;
};

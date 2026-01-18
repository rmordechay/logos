#pragma once
#include "LgsIterable.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        isHeapAlloc = true;
        passByRef = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* isReturnExpr = nullptr, Value* pointee = nullptr) override;
    LgsType* replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) override;
    void addIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index, LgsExpr* value) override;
    Value* getDataField(LgsCgModule& cg, Value* iterable);
    Value* getLenField(LgsCgModule& cg, Value* iterable);
    Value* getCapField(LgsCgModule& cg, Value* iterable);
    Function* generateContainsFunc(LgsCgModule& cg);
    Function* generateAddFunc(LgsCgModule& cg);
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    LgsType* clone() override;
};

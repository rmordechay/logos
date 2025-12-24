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
        passByRef = true;
        isHeapAlloc = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee) override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

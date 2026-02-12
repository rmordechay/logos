#pragma once
#include "LgsIterable.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr std::string name = "DArray";

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        isHeap = true;
        passByRef = true;
        rttKind = RTT_DARRAY;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterable, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    Function* getAddFunc(LgsCodeGen& cg);
    Function* getContainsFunc(LgsCodeGen& cg);
    Function* getEqFunc(LgsCodeGen& cg);
    DIType* getDebugType(LgsCodeGen& cg) override;
};

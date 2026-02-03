#pragma once
#include "LgsIterable.h"
#include "LgsRTTIndices.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    inline static Lgs_DArrayExprIndices rttIndices;

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        isHeapAlloc = true;
        passByRef = true;
        rttKind = RTT_DARRAY;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterable, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Function* generateAddFunc(LgsCodeGen& cg);
    Function* generateContainsFunc(LgsCodeGen& cg);
    Function* generateArrEqFunc(LgsCodeGen& cg);
    DIType* getDebugType(LgsCodeGen& cg) override;
};

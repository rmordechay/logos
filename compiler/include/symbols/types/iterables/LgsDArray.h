#pragma once
#include "LgsIterable.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    const size_t levelIndex = 0;
    const size_t typeIndex = 1;
    const size_t dataIndex = 2;
    const size_t lenIndex = 3;
    const size_t capIndex = 4;

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        isHeapAlloc = true;
        passByRef = true;
        rtt = RTT_DARRAY;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    LgsType* replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterable, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    Function* generateArrEqFunc(LgsCodeGen& cg);
    Function* generateContainsFunc(LgsCodeGen& cg);
    Function* generateAddFunc(LgsCodeGen& cg);
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsType* clone() override;
};

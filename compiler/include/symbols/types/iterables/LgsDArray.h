#pragma once
#include "LgsIterable.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsVoid.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, nullptr}, BUILTIN | PUBLIC | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        passByRef = true;
        isHeapAlloc = true;
        addFunc->fn = getAddFn();
        addMethod(addFunc);
    }
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
    CallFn getAddFn();
};

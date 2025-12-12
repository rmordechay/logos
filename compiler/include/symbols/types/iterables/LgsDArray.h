#pragma once
#include "LgsIterable.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC_NAME, name, &LGS_VOID, {this, nullptr}, BUILTIN | PUBLIC | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        passByRef = true;
        isHeapAlloc = true;
        addFunc->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            const auto arr = args[0].expr->IRValue;
            const auto arg = args[1].expr;
            if (args[1].expr->type->asInt()) {
                return cg.callLgsFunc(std::string(name) + "_addInt", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.i32Ty()}, {arr, getRTType(cg), arg->IRValue});
            }
            if (args[1].expr->type->asLong()) {
                return cg.callLgsFunc(std::string(name) + "_addLong", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.i64Ty()}, {arr, getRTType(cg), arg->IRValue});
            }
            if (args[1].expr->type->asSize()) {
                return cg.callLgsFunc(std::string(name) + "_addSize", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.sizeTy()}, {arr, getRTType(cg), arg->IRValue});
            }
            return cg.callLgsFunc(std::string(name) + "_add", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, {arr, getRTType(cg), arg->IRValue});
        };
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
    ~LgsDArray() override;
};

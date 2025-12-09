#pragma once
#include "types/LgsAny.h"
#include "types/iterables/LgsIterable.h"
#include "types/primitives/LgsVoid.h"

using llvm::StructType;

class LgsSet final : public LgsIterable {
public:
    static constexpr auto name = "Set";
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC_NAME, name, &LGS_VOID, {this, &LGS_ANY}, BUILTIN | PUBLIC | METHOD);

    explicit LgsSet(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        passByRef = true;
        isHeapAlloc = true;
        addMethod(addFunc);
    }
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

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
    Type* getIRType(LgsLLVMGen& cg) override;
    Constant* getRTType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    Value* lenIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
};

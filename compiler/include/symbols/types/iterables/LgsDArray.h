#pragma once
#include "LgsIterable.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"

#define RESERVE_FUNC_NAME "reserve"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC_NAME, name, &LGS_VOID, {this, &LGS_ANY}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* reserveFunc = new LgsFunc(RESERVE_FUNC_NAME, name, &LGS_VOID, {this, &LGS_SIZE}, BUILTIN | PUBLIC | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        passByRef = true;
        isHeapAlloc = true;
        addMethod(addFunc);
        addMethod(reserveFunc);
    }
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsLLVMGen& cg) override;
    Constant* getRTType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    std::string getGenericName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    Value* lenIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
};

#pragma once
#include <string>
#include <vector>

#include "funcs/LgsFunc.h"
#include "../primitives/LgsAny.h"
#include "types/iterables/LgsIterable.h"
#include "types/primitives/LgsVoid.h"
#include "LgsValue.h"
#include "types/LgsFuncType.h"

class LgsType;
namespace llvm {
class StructType;
}

using llvm::StructType;

class LgsSet final : public LgsIterable {
public:
    static constexpr auto name = "Set";
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, &LGS_ANY}, BUILTIN | PUBLIC | METHOD);

    explicit LgsSet(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        isHeap = true;
        passByRef = true;
        addMethod(addFunc);
    }
    Type* getIRType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
};

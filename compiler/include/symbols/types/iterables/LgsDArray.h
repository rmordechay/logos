#pragma once
#include "LgsIterable.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"

#define RESERVE_FUNC_NAME "reserve"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC_NAME, name, &LGS_VOID, {this, nullptr}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* reserveFunc = new LgsFunc(RESERVE_FUNC_NAME, name, &LGS_VOID, {this, &LGS_SIZE}, BUILTIN | PUBLIC | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        passByRef = true;
        isHeapAlloc = true;
        addMethod(addFunc);
        addMethod(reserveFunc);
        addFunc->fn = addFuncImpl;
    }
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    std::string pname() override;
    std::string getGenericName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string fmtStr() const override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    DIType* getDebugType(LgsCgModule& cg) override;
    static Value* addFuncImpl(LgsCgModule& cg, const std::vector<LgsFuncArg>& args);
    ~LgsDArray() override;
};

#pragma once
#include "LgsAny.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "LgsVoid.h"
#include "funcs/LgsFunc.h"
#include "primitives/LgsSize.h"
#include "types/LgsIterable.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;
    LgsFunc* addFunc = new LgsFunc("add", &LGS_VOID, {this, &LGS_ANY}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* lenFunc = new LgsFunc("len", &LGS_INT, {this}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* getFunc = new LgsFunc("get", &LGS_ANY, {this, &LGS_LONG}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* isEmptyFunc = new LgsFunc("isEmpty", &LGS_BOOL, {this}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* isNotEmptyFunc = new LgsFunc("isNotEmpty", &LGS_BOOL, {this}, INTERNAL | PUBLIC | METHOD);
    LgsFunc* initFunc = new LgsFunc("init", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD);
    LgsFunc* putFunc = new LgsFunc("put", &LGS_VOID, {this, &LGS_INT, &LGS_ANY}, INTERNAL | METHOD);
    LgsFunc* deleteFunc = new LgsFunc("delete", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD);
    LgsFunc* freeFunc = new LgsFunc("free", &LGS_VOID, {this}, INTERNAL | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addFunc->fn = [this](LgsLLVM& cg, const std::vector<LgsExpr*>& args) {
            return callAdd(cg, args);
        };
        addMethod(addFunc);
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
        isSliceable = true;
    }

    Value* callAdd(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) const;
    Type* getIRType(LgsLLVM& codeGen) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsLLVM& codeGen);
    void freeValue(LgsLLVM& codeGen, Value* value) override;
    Value* IRLength(LgsLLVM& codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
    json::value asJSON() override;
};

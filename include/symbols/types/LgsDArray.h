#pragma once
#include "LgsAny.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "LgsVoid.h"
#include "funcs/LgsFunc.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsFunc {
public:
    LgsType* parent;
    explicit LgsArrayAddFunc(LgsType* parentType) : LgsFunc("add", &LGS_VOID, {parentType, &LGS_ANY}, PUBLIC | INTERNAL | METHOD), parent(parentType) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override;
    ~LgsArrayAddFunc() override = default;
};

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;
    LgsArrayAddFunc* addFunc = new LgsArrayAddFunc(this);
    LgsFunc* lenFunc = new LgsFunc("len", &LGS_INT, {this}, INTERNAL | METHOD | PUBLIC);
    LgsFunc* getFunc = new LgsFunc("get", &LGS_ANY, {this, &LGS_LONG}, INTERNAL | METHOD | PUBLIC);
    LgsFunc* isEmptyFunc = new LgsFunc("isEmpty", &LGS_BOOL, {this}, INTERNAL | METHOD | PUBLIC);
    LgsFunc* isNotEmptyFunc = new LgsFunc("isNotEmpty", &LGS_BOOL, {this}, INTERNAL | METHOD | PUBLIC);
    LgsFunc* initFunc = new LgsFunc("init", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD);
    LgsFunc* putFunc = new LgsFunc("put", &LGS_VOID, {this, &LGS_LONG, &LGS_ANY}, INTERNAL | METHOD);
    LgsFunc* deleteFunc = new LgsFunc("delete", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD);
    LgsFunc* freeFunc = new LgsFunc("free", &LGS_VOID, {this}, INTERNAL | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        addMethod(addFunc);
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
        isSliceable = true;
    }
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsCodeGen* codeGen);
    void freeValue(LgsCodeGen* codeGen, Value* value) override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsDArray() override;
};

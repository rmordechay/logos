#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "primitives/LgsVoid.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsBuiltinFunc {
public:
    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getIRName(), {parent, &LGS_ANY}, true, true) {}
    Value* call(LgsModule* runtime, const vector<LgsExpr*>& args) override;
    Type* getIRFuncType(LLVMContext& context) override;
    ~LgsArrayAddFunc() override = default;
};

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";

    StructType* arrStruct = nullptr;
    LgsArrayAddFunc addFunc{this};
    LgsBuiltinFunc lenFunc{"len", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc getFunc{"get", &LGS_ANY, name, {this, &LGS_LONG}, true};
    LgsBuiltinFunc isEmptyFunc{"isEmpty", &LGS_BOOL, name, {this}, true};
    LgsBuiltinFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, name, {this}, true};
    LgsBuiltinFunc initFunc{"init", &LGS_VOID, name, {this, &LGS_LONG, &LGS_LONG}};
    LgsBuiltinFunc putFunc{"put", &LGS_VOID, name, {this, &LGS_LONG, &LGS_ANY}};
    LgsBuiltinFunc deleteFunc{"delete", &LGS_VOID, name, {this, &LGS_LONG}};
    LgsBuiltinFunc freeFunc{"free", &LGS_VOID, name, {this}};

    explicit LgsArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        unpackLength = 1;
        addMethod(&addFunc);
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
        canSlice = true;
    }

    Type* getIRType(LLVMContext& context) override;
    string getIRName() override;
    string prettyName() const override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    string getStrFormatPart() const override;
    Value* getLength(LgsModule* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsModule* runtime, LgsExpr* expr) override;
    Value* isEmpty(LgsModule* runtime, LgsExpr* expr) override;
    Value* isNotEmpty(LgsModule* runtime, LgsExpr* expr) override;
    StructType* getArrStruct(LLVMContext& context);
    bool equals(LgsType* other) override;
    ~LgsArray() override;
};

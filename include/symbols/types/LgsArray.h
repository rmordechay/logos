#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsLong.h"
#include "primitives/LgsVoid.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsBuiltinFunc {
public:
    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getIRName(), {parent, &LGS_ANY}, true, true) {}
    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override;
    ~LgsArrayAddFunc() override = default;
};

class LgsArray final : public LgsIterable {
public:
    static constexpr auto name = "Array";

    StructType* arrStruct = nullptr;
    LgsArrayAddFunc addFunc{this};
    LgsBuiltinFunc lenFunc{"len", &LGS_LONG, name, {this}, true};
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

    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    void unpackTypes(const vector<LgsVarDec*>& varDecs) override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* isEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* isNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    StructType* getArrStruct(LgsRuntime* runtime);
    LgsType* clone() override;
    ~LgsArray() override;
};

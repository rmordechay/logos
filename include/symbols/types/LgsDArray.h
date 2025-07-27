#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "LgsVoid.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsBuiltinFunc {
public:
    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getName(), {parent, &LGS_ANY}, true) {}
    Value* call(LgsModule* module, const vector<LgsExpr*>& args) override;
    ~LgsArrayAddFunc() override = default;
};

class LgsDArray final : public LgsIterable {
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

    explicit LgsDArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        unpackLength = 1;
        addMethod(&addFunc);
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
        canSlice = true;
    }
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    string prettyName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    string getStrFormatPart() const override;
    Value* getLength(LgsModule* module, LgsExpr* expr) override;
    Value* getLoopLength(LgsModule* module, LgsExpr* expr) override;
    Value* isEmpty(LgsModule* module, LgsExpr* expr) override;
    Value* isNotEmpty(LgsModule* module, LgsExpr* expr) override;
    StructType* getArrStruct(LgsModule* module);
    bool equals(LgsType* other) override;
    ~LgsDArray() override;
};

#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "LgsVoid.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsShort.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsBuiltinFunc {
public:
    LgsBuiltinFunc addBoolFunc{"addBool", &LGS_VOID};
    LgsBuiltinFunc addByteFunc{"addByte", &LGS_VOID};
    LgsBuiltinFunc addShortFunc{"addShort", &LGS_VOID};
    LgsBuiltinFunc addIntFunc{"addInt", &LGS_VOID};
    LgsBuiltinFunc addLongFunc{"addLong", &LGS_VOID};
    explicit LgsArrayAddFunc(LgsType* parent) : LgsBuiltinFunc("add", &LGS_VOID, parent->getName(), {parent, &LGS_ANY}, true) {
        addBoolFunc.init(parent->getName(), {parent, &LGS_BOOL});
        addByteFunc.init(parent->getName(), {parent, &LGS_CHAR});
        addShortFunc.init(parent->getName(), {parent, &LGS_SHORT});
        addIntFunc.init(parent->getName(), {parent, &LGS_INT});
        addLongFunc.init(parent->getName(), {parent, &LGS_LONG});
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
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
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    string strFormatPart() const override;
    StructType* getArrStruct(LgsCodeGen* codeGen);
    void freeValue(LgsCodeGen* codeGen, Value* value) override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsDArray() override;
};

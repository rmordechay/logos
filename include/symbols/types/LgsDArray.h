#pragma once
#include "LgsAny.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsLong.h"
#include "LgsVoid.h"
#include "funcs/LgsFunc.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsShort.h"
#include "types/LgsIterable.h"

class LgsArrayAddFunc final : public LgsFunc {
public:
    LgsType* parent;
    LgsFunc addBoolFunc{"addBool", &LGS_VOID, {parent, &LGS_BOOL}, INTERNAL | METHOD};
    LgsFunc addByteFunc{"addByte", &LGS_VOID, {parent, &LGS_CHAR}, INTERNAL | METHOD};
    LgsFunc addShortFunc{"addShort", &LGS_VOID, {parent, &LGS_SHORT}, INTERNAL | METHOD};
    LgsFunc addIntFunc{"addInt", &LGS_VOID, {parent, &LGS_INT}, INTERNAL | METHOD};
    LgsFunc addLongFunc{"addLong", &LGS_VOID, {parent, &LGS_LONG}, INTERNAL | METHOD};
    explicit LgsArrayAddFunc(LgsType* parentType) : LgsFunc("add", &LGS_VOID, {parentType, &LGS_ANY}, PUBLIC | INTERNAL | METHOD), parent(parentType) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override;
    ~LgsArrayAddFunc() override = default;
};

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;
    LgsArrayAddFunc addFunc{this};
    LgsFunc lenFunc{"len", &LGS_INT, {this}, INTERNAL | METHOD | PUBLIC};
    LgsFunc getFunc{"get", &LGS_ANY, {this, &LGS_LONG}, INTERNAL | METHOD | PUBLIC};
    LgsFunc isEmptyFunc{"isEmpty", &LGS_BOOL, {this}, INTERNAL | METHOD | PUBLIC};
    LgsFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, {this}, INTERNAL | METHOD | PUBLIC};
    LgsFunc initFunc{"init", &LGS_VOID, {this, &LGS_LONG, &LGS_LONG}, INTERNAL | METHOD};
    LgsFunc putFunc{"put", &LGS_VOID, {this, &LGS_LONG, &LGS_ANY}, INTERNAL | METHOD};
    LgsFunc deleteFunc{"delete", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD};
    LgsFunc freeFunc{"free", &LGS_VOID, {this}, INTERNAL | METHOD};

    explicit LgsDArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        addMethod(&addFunc);
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
        canSlice = true;
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

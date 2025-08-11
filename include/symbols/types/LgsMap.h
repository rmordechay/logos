#pragma once
#include "LgsAny.h"
#include "LgsStr.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsInt.h"
#include "LgsVoid.h"
#include "types/LgsTypePair.h"

class LgsMapEntry;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    StructType* mapStruct = nullptr;
    LgsTypePair* typePair = nullptr;
    LgsBuiltinFunc getFunc{"get", &LGS_ANY, name, {this, new LgsStr()}, true};
    LgsBuiltinFunc addFunc{"add", &LGS_VOID, name, {this, new LgsStr(), &LGS_ANY}, true};
    LgsBuiltinFunc lenFunc{"len", &LGS_LONG, name, {this}, true};
    LgsBuiltinFunc isEmptyFunc{"isEmpty", &LGS_BOOL, name, {this}, true};
    LgsBuiltinFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, name, {this}, true};
    LgsBuiltinFunc initFunc{"init", &LGS_VOID, name, {this, &LGS_LONG}};
    LgsBuiltinFunc deleteFunc{"delete", &LGS_VOID, name, {this, &LGS_ANY}};
    LgsBuiltinFunc freeFunc{"free", &LGS_VOID, name, {this}};

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        typePair = new LgsTypePair(keyType, valueType);
        baseType = typePair;
        unpackLength = 2;
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
    }

    size_t getSizeBytes() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    StructType* getMapStruct(LgsCodeGen* codeGen);
    bool equals(LgsType* other) override;
    void freeValue(LgsCodeGen* codeGen, Value* value) override;
    ~LgsMap() override = default;
};

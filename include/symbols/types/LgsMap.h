#pragma once
#include "LgsAny.h"
#include "LgsStr.h"
#include "primitives/LgsInt.h"
#include "LgsVoid.h"
#include "types/LgsTypePair.h"

class LgsMapEntry;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    StructType* mapStruct = nullptr;
    LgsTypePair* typePair = nullptr;
    LgsFunc getFunc{"get", &LGS_ANY, {this, new LgsStr()}, PUBLIC | INTERNAL | METHOD};
    LgsFunc addFunc{"add", &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, PUBLIC | INTERNAL | METHOD};
    LgsFunc lenFunc{"len", &LGS_LONG, {this}, PUBLIC | INTERNAL | METHOD};
    LgsFunc isEmptyFunc{"isEmpty", &LGS_BOOL, {this}, PUBLIC | INTERNAL | METHOD};
    LgsFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, {this}, PUBLIC | INTERNAL | METHOD};
    LgsFunc initFunc{"init", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD};
    LgsFunc deleteFunc{"delete", &LGS_VOID, {this, &LGS_ANY}, INTERNAL | METHOD};
    LgsFunc freeFunc{"free", &LGS_VOID, {this}, INTERNAL | METHOD};

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
    std::string getName() override;
    std::string prettyName() override;
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

#pragma once
#include "LgsAny.h"
#include "LgsStr.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsVoid.h"
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
    Type* getIRType(LgsModule* module) override;
    string getName() override;
    string prettyName() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    Value* getLength(LgsModule* module, LgsExpr* expr) override;
    Value* getLoopLength(LgsModule* module, LgsExpr* expr) override;
    Value* isEmpty(LgsModule* module, LgsExpr* expr) override;
    Value* isNotEmpty(LgsModule* module, LgsExpr* expr) override;
    StructType* getMapStruct(LgsModule* runtime);
    bool equals(LgsType* other) override;
    ~LgsMap() override = default;
};

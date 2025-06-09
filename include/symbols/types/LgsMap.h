#pragma once
#include "LgsAny.h"
#include "LgsStr.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsInt.h"
#include "primitives/LgsVoid.h"
#include "types/LgsPair.h"

class LgsMapPair;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair kvType;
    StructType* mapStruct = nullptr;

    LgsBuiltinFunc getFunc{"get", &LGS_ANY, name, {this, new LgsStr()}, true};
    LgsBuiltinFunc addFunc{"add", &LGS_VOID, name, {this, new LgsStr(), &LGS_ANY}, true};
    LgsBuiltinFunc lenFunc{"len", &LGS_LONG, name, {this}, true};
    LgsBuiltinFunc isEmptyFunc{"isEmpty", &LGS_BOOL, name, {this}, true};
    LgsBuiltinFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, name, {this}, true};
    LgsBuiltinFunc initFunc{"init", &LGS_VOID, name, {this, &LGS_LONG}};
    LgsBuiltinFunc deleteFunc{"delete", &LGS_VOID, name, {this, &LGS_ANY}};
    LgsBuiltinFunc freeFunc{"free", &LGS_VOID, name, {this}};

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&kvType) {
        kvType.key = keyType;
        kvType.value = valueType;
        unpackLength = 2;
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
    }

    void setBaseType(const vector<LgsMapPair*>& exprs);
    size_t getSizeBytes() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* getBaseType() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    void unpackTypes(const vector<LgsVarDec*>& varDecs) override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    ~LgsMap() override = default;
    StructType* getMapStruct(LgsRuntime* runtime);
};



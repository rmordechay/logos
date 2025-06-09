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
    LgsBuiltinFunc get{"get", &LGS_ANY, name, {this, new LgsStr()}, true};
    LgsBuiltinFunc add{"add", &LGS_VOID, name, {this, new LgsStr(), &LGS_ANY}, true};
    LgsBuiltinFunc len{"len", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc isEmpty{"isEmpty", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc isNotEmpty{"isNotEmpty", &LGS_INT, name, {this}, true};
    LgsBuiltinFunc init{"init", &LGS_VOID, name, {this, &LGS_INT}};
    LgsBuiltinFunc delete_{"delete", &LGS_VOID, name, {this, &LGS_ANY}};
    LgsBuiltinFunc free{"free", &LGS_VOID, name, {this}};

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&kvType) {
        kvType.key = keyType;
        kvType.value = valueType;
        unpackLength = 2;
        addMethod(&len);
        addMethod(&isEmpty);
        addMethod(&isNotEmpty);
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



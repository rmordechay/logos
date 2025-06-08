#pragma once
#include "methods/LgsMapMethods.h"
#include "types/LgsPair.h"

class LgsMapPair;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair kvType;
    StructType* mapStruct = nullptr;
    LgsMapInitFunc init{this};
    LgsMapGetFunc get{this};
    LgsMapAddFunc add{this};
    LgsMapLenFunc len{this};
    LgsMapIsEmptyFunc isEmpty{this};
    LgsMapIsNotEmptyFunc isNotEmpty{this};
    LgsMapDeleteFunc delete_{this};

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
    Type* getIRType(LgsRuntime* runtime) override;
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
};



#pragma once
#include "LgsDArray.h"
#include "LgsStr.h"
#include "types/LgsAny.h"
#include "types/LgsTypePair.h"
#include "types/primitives/LgsVoid.h"

#define KEYS_FUNC_NAME "keys"
#define VALUES_FUNC_NAME "values"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsTypePair* mapType = nullptr;
    LgsFunc* addFunc = new LgsFunc(ADD_FUNC_NAME, name, &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, PUBLIC | BUILTIN | METHOD);
    LgsFunc* keysFunc;
    LgsFunc* valuesFunc;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr): LgsIterable(new LgsTypePair(keyType, valueType)) {
        mapType = baseType->asPair();
        isHeapAlloc = true;
        passByRef = true;
        keysFunc = new LgsFunc(KEYS_FUNC_NAME, name, new LgsDArray(mapType->key), {this}, BUILTIN | PUBLIC | METHOD);
        valuesFunc = new LgsFunc(VALUES_FUNC_NAME, name, new LgsDArray(mapType->value), {this}, BUILTIN | PUBLIC | METHOD);
        addMethod(addFunc);
        addMethod(keysFunc);
        addMethod(valuesFunc);
    }

    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    bool unpackLoopVarsTypes(LgsForeachLoop* loop) const override;
    void unpackLoopIR(LgsCgModule& cg, LgsForeachLoop* loop) const override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

class LgsPair final {
public:
    LgsExpr* key;
    LgsExpr* value;
};
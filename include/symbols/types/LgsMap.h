#pragma once
#include "LgsAny.h"
#include "LgsStr.h"
#include "LgsVoid.h"
#include "types/LgsTypePair.h"

class LgsMapEntry;

class LgsMapAddFunc final : public LgsFunc {
public:
    LgsType* parent;
    explicit LgsMapAddFunc(LgsType* parentType) : LgsFunc("add", &LGS_VOID, {parentType, new LgsStr(), &LGS_ANY}, PUBLIC | INTERNAL | METHOD), parent(parentType) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override;
};

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    StructType* mapStruct = nullptr;
    LgsTypePair* typePair = nullptr;
    LgsMapAddFunc* addFunc = new LgsMapAddFunc(this);
    LgsFunc* initFunc = new LgsFunc("init", &LGS_VOID, {this, &LGS_LONG}, INTERNAL | METHOD);
    LgsFunc* getFunc = new LgsFunc("get", &LGS_ANY, {this, new LgsStr()}, PUBLIC | INTERNAL | METHOD);
    LgsFunc* lenFunc = new LgsFunc("len", &LGS_LONG, {this}, PUBLIC | INTERNAL | METHOD);
    LgsFunc* isEmptyFunc = new LgsFunc("isEmpty", &LGS_BOOL, {this}, PUBLIC | INTERNAL | METHOD);
    LgsFunc* isNotEmptyFunc = new LgsFunc("isNotEmpty", &LGS_BOOL, {this}, PUBLIC | INTERNAL | METHOD);
    LgsFunc* deleteFunc = new LgsFunc("delete", &LGS_VOID, {this, &LGS_ANY}, INTERNAL | METHOD);
    LgsFunc* freeFunc = new LgsFunc("free", &LGS_VOID, {this}, INTERNAL | METHOD);

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        typePair = new LgsTypePair(keyType, valueType);
        baseType = typePair;
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
    }

    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    StructType* getMapStruct(LgsCodeGen* codeGen);
    bool canCastTo(LgsType* other) override;
    void freeValue(LgsCodeGen* codeGen, Value* value) override;
    std::string strFormatPart() const override;
    ~LgsMap() override;
};

#pragma once
#include "LgsAny.h"
#include "LgsStr.h"
#include "LgsVoid.h"
#include "types/LgsTypePair.h"

class LgsMapEntry;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    StructType* mapStruct = nullptr;
    LgsTypePair* typePair = nullptr;
    LgsFunc* addFunc = new LgsFunc("add", &LGS_VOID, {this, new LgsStr(), &LGS_ANY}, PUBLIC | INTERNAL | METHOD);
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
        addFunc->fn = [this](LgsLLVM& cg, const std::vector<LgsExpr*>& args) {
            return callAdd(cg, args);
        };
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
    }

    Value* callAdd(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) const;
    Type* getIRType(LgsLLVM& codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsLLVM& codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) override;
    StructType* getMapStruct(LgsLLVM& codeGen);
    bool canCastTo(LgsType* other) override;
    void freeValue(LgsLLVM& codeGen, Value* value) override;
    std::string strFormatPart() const override;
    ~LgsMap() override;
};

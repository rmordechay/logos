#pragma once
#include "LgsStr.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsTypePair.h"
class LgsMapEntry;

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    StructType* mapStruct = nullptr;
    LgsTypePair* typePair = nullptr;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        typePair = new LgsTypePair(keyType, valueType);
        baseType = typePair;
        isHeapAlloc = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJsonStr() override;
    LgsFunc* getAddFunc() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    StructType* getMapStruct(LgsLLVMGen& cg);
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    ~LgsMap() override;
};

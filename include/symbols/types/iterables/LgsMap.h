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
    LgsFunc* getFunc = new LgsFunc("get", &LGS_ANY, {this, new LgsStr()}, PUBLIC | BUILTIN | METHOD);

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        typePair = new LgsTypePair(keyType, valueType);
        baseType = typePair;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    LgsFunc* getAddFunc() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsLLVMGen& cg, Value* iterable) override;
    StructType* getMapStruct(LgsLLVMGen& cg);
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    ~LgsMap() override;
};

#pragma once
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsLong.h"
#include "funcs/LgsFunc.h"
#include "LgsIterable.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;
    LgsFunc* getFunc = new LgsFunc("get", &LGS_ANY, {this, &LGS_LONG}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* mapFunc = new LgsFunc("map", this, {this, new LgsFuncType(nullptr, {LgsParam(nullptr)})}, BUILTIN | PUBLIC | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addMethod(mapFunc);
        rtt = RTT_DARRAY;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsLLVMGen& cg);
    LgsFunc* getAddFunc() override;
    Value* IRLength(LgsLLVMGen& cg, Value* iterable) override;
    bool canCastTo(LgsType* other) override;
    json::value asJSON() override;
};

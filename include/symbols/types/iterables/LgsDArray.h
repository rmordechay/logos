#pragma once
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/LgsVoid.h"
#include "funcs/LgsFunc.h"
#include "types/primitives/LgsSize.h"
#include "LgsIterable.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;
    LgsFunc* addFunc = new LgsFunc("add", &LGS_VOID, {this, &LGS_ANY}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* lenFunc = new LgsFunc("len", &LGS_SIZE, {this}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* getFunc = new LgsFunc("get", &LGS_ANY, {this, &LGS_LONG}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* isEmptyFunc = new LgsFunc("isEmpty", &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* isNotEmptyFunc = new LgsFunc("isNotEmpty", &LGS_BOOL, {this}, BUILTIN | PUBLIC | METHOD);
    LgsFunc* initFunc = new LgsFunc("init", &LGS_VOID, {this, &LGS_LONG}, BUILTIN | METHOD);
    LgsFunc* putFunc = new LgsFunc("put", &LGS_VOID, {this, &LGS_INT, &LGS_ANY}, BUILTIN | METHOD);
    LgsFunc* deleteFunc = new LgsFunc("delete", &LGS_VOID, {this, &LGS_LONG}, BUILTIN | METHOD);
    LgsFunc* freeFunc = new LgsFunc("free", &LGS_VOID, {this}, BUILTIN | METHOD);
    LgsFunc* mapFunc = new LgsFunc("map", this, {this, new LgsFuncType(nullptr, {LgsParam(nullptr)})}, BUILTIN | PUBLIC | METHOD);

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addFunc->fn = [this](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
            return addFunc->callIR(cg, {args[0]->IRValue, args[1]->getIRPtrTo(cg)});
        };
        addMethod(addFunc);
        addMethod(lenFunc);
        addMethod(isEmptyFunc);
        addMethod(isNotEmptyFunc);
        addMethod(mapFunc);
        isSliceable = true;
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
    void freeValue(LgsLLVMGen& cg, Value* value) override;
    Value* IRLength(LgsLLVMGen& cg, Value* iterable) override;
    Value* IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
    json::value asJSON() override;
};

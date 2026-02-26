#pragma once
#include <llvm/IR/DerivedTypes.h>
#include <string>

#include "LgsIterable.h"
#include "Lgs_Types.h"
#include "types/LgsTypeParam.h"

class LgsCodeGen;
class LgsType;

namespace llvm {
    class Function;
class StructType;
class Value;
}

class LgsDArray final : public LgsIterable {
public:
    static constexpr std::string name = "DArray";

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        isHeap = true;
        passByRef = true;
        rttKind = RTT_DARRAY;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterable, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCodeGen& cg, Value* iterable, Value* index, Value* value) override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    Function* getAddFunc(LgsCodeGen& cg);
    Function* getContainsFunc(LgsCodeGen& cg);
    Function* getEqFunc(LgsCodeGen& cg);
    DIType* getDebugType(LgsCodeGen& cg) override;
    LgsDArray* clone() override;
    static Value* loadRTBaseType(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTLength(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTCapacity(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTData(LgsCodeGen& cg, Value* ptr);
    static StructType* getRTTStruct(LgsCodeGen& cg);
};

#pragma once
#include <string>

#include "LgsConfigs.h"
#include "LgsIterable.h"
#include "types/primitives/LgsChar.h"
#include "LgsValue.h"
#include "Lgs_Types.h"

class LgsCodeGen;
namespace llvm {
class Constant;
class Type;
class Value;
}

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    size_t const length;

    explicit LgsStr(const size_t len = 0): LgsIterable(&LGS_CHAR), length(len) {
        isHeap = true;
        passByRef = true;
        rttKind = RTT_STR;
    }
    Type* getIRType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::optional<size_t> getConstLength() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    static Type* getStrStruct(LgsCodeGen& cg);
    static void storeData(LgsCodeGen& cg, Value* ptr, Value* value);
    static Value* loadIRData(LgsCodeGen& cg, Value* value);
    static Constant* getStrConst(LgsCodeGen& cg, const std::string& text);
    static Value* getEmptyIRStr(LgsCodeGen& cg, Value* size);
};

inline LgsStr LGS_STR;
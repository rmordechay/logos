#pragma once
#include "LgsIntConst.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsStrConst final : public LgsExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> parts;
    bool isSingleQuoted;

    explicit LgsStrConst(const std::string& value) : value(value) {
        isValueKnown = true;
        if (value.size() == 1) {
            setType(&LGS_CHAR);
        } else {
            const auto lgsStr = new LgsStr();
            lgsStr->isStatic = true;
            lgsStr->size = new LgsIntConst(&LGS_INT, value.size());
            setType(lgsStr);
        }
    }
    LgsExpr* staticCast(LgsType* toType, bool explicitCast) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    Value* hashValue(LgsLLVMGen& cg) override;
    void hashNode(size_t& oldHash) override;
    bool equals(LgsExpr* other) override;
    LgsStrConst* clone() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    ~LgsStrConst() override;
};

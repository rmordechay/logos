#pragma once
#include "LgsIntConst.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsStrConst final : public LgsExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> parts;

    explicit LgsStrConst(const std::string& v) : value(v) {
        isMutable = false;
        if (v.size() == 1) {
            type = &LGS_CHAR;
        } else {
            const auto lgsStr = new LgsStr();
            lgsStr->isStatic = true;
            lgsStr->size = new LgsIntConst(&LGS_INT, v.size());
            type = lgsStr;
        }
    }
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* loadIR(LgsCgModule& cg) override;
    std::string asText() override;
    Value* hashValue(LgsCgModule& cg) override;
    void hashNode(size_t& oldHash) override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsStrConst() override;
};

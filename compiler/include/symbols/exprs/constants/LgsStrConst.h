#pragma once
#include "LgsIntConst.h"
#include "types/iterables/LgsStr.h"

class LgsStrConst final : public LgsExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> parts;

    explicit LgsStrConst(const std::string& v) : value(v) {
        const auto str = new LgsStr();
        str->isStatic = true;
        isMutable = false;
        type = str;
    }
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* loadIR(LgsCgModule& cg) override;
    std::string asText() override;
    void hashNode(size_t& oldHash) override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsStrConst() override;
};

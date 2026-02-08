#pragma once
#include "types/iterables/LgsStr.h"

class LgsStrConst final : public LgsExpr {
public:
    std::string value;
    std::string formatedStr = "";
    std::vector<LgsExpr*> parts;

    explicit LgsStrConst(const std::string& v) : value(v) {
        const auto str = new LgsStr();
        str->isStatic = true;
        type = str;
    }
    Value* loadIR(LgsCodeGen& cg) override;
    std::string asText() override;
    void hashNode(size_t& oldHash) override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() override;
    ~LgsStrConst() override;
};

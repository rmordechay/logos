#pragma once
#include "exprs/LgsExpr.h"


class LgsStr;
class LgsMap;
class LgsDArray;
struct LgsIndex;

class LgsIterIndex final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsIndex* index = nullptr;

    explicit LgsIterIndex(LgsExpr* baseExpr, LgsIndex* index = nullptr) : baseExpr(baseExpr), index(index) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* loadFromDArray(LgsLLVMGen& cg, const LgsDArray* arr) const;
    Value* loadFromMap(LgsLLVMGen& cg, const LgsMap* map) const;
    Value* loadFromStr(LgsLLVMGen& cg) const;
    Value* loadFromVec(LgsLLVMGen& cg) const;
    Value* loadFromSArray(LgsLLVMGen& cg) const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    void assignScalar(LgsLLVMGen& cg, LgsExpr* expr);
    void assignArray(LgsLLVMGen& cg, const LgsArrayExpr* arr) const;
    void assignHashMap(LgsLLVMGen& cg, LgsHashMap* map);
    bool canAssignTo(LgsType* other, LgsAssignType op) override;
    std::string pname() override;
    json::value asJSON() override;
    ~LgsIterIndex() override;
};

struct LgsIndex {
    LgsExpr* from;
    LgsExpr* to;

    ~LgsIndex() {
        if (from) {
            delete from;
            from = nullptr;
        }
        if (to) {
            delete to;
            to = nullptr;
        }
    }
};



#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsExpr {
public:
    std::string name;
    LgsObject* obj = nullptr;
    std::map<std::string, LgsExpr*> args;
    std::vector<LgsType*> generics;

    explicit LgsInstance(const std::string& name): name(name) {}
    explicit LgsInstance(LgsObject* obj) : LgsExpr(obj), name(obj->name), obj(obj) {}
    std::string asText() override;
    LgsExpr* castTo(LgsType* toType, bool explicitCast) override;
    Value* castToIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    void hashNode(size_t& oldHash) override;
    void setObject(LgsObject* newObj);
    bool equals(LgsExpr* other) override;
    ~LgsInstance() override;
};

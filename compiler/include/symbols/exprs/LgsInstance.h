#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"

struct LgsInstanceArg {
    std::string name = "";
    LgsExpr* expr = nullptr;
    LgsInstanceArg(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {}
};

class LgsInstance final : public LgsExpr {
public:
    std::string name;
    LgsObject* obj = nullptr;
    std::vector<LgsField*> fields;
    std::map<std::string, LgsInstanceArg> args;
    std::vector<LgsType*> generics;

    explicit LgsInstance(const std::string& name): name(name) {}
    explicit LgsInstance(LgsObject* obj) : LgsExpr(obj), name(obj->name), obj(obj) {}
    std::string asText() override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* loadIR(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    void setObject(LgsObject* newObj);
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsField* getField(const std::string& fieldName) const;
    ~LgsInstance() override;
};

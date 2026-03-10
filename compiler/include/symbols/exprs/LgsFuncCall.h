#pragma once
#include <string>
#include <vector>

#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
#include "stmts/LgsVarDec.h"

class LgsFuncType;
struct LgsSymbol;
class LgsFunc;
class LgsType;

class LgsFuncCall final : public LgsExpr {
public:
    std::string name;
    std::vector<LgsVarDec> args;
    std::vector<LgsType*> typeArgs;
    LgsFunc* func = nullptr;
    LgsFunc* coroutine = nullptr;
    bool inSelection = false;
    bool isDeferred = false;
    bool isNamed = false;
    bool isMock = false;
    LgsSymbol ref;

    explicit LgsFuncCall(const std::string& name) : name(name) {}
    bool equals(LgsFuncType* funcType) const;
    std::string asText() override;
    std::string mangleName() const;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsFuncCall* clone() const override;
    ~LgsFuncCall() override;
};

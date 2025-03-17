#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    string composedName;
    vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    Location position = Location();

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setComposedName();
    ~LgsFuncCall() override;
};

inline void LgsFuncCall::setComposedName() {
    auto tempName = name;
    for (int i = 0; i < args.size(); ++i) {
        tempName += "_" + args[i]->type->getName();
    }
    composedName = tempName;
}

#endif //LOGOSFUNCCALLEXPR_H

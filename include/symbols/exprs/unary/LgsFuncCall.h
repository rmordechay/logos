#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"
#include "funcs/LgsFuncSignature.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    vector<LgsExpr*> args;
    LgsFuncSignature signature;
    LgsFunc* func = nullptr;

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : args(args) {
        signature.name = name;
    }

    string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getArgsTypeStr() const;
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H

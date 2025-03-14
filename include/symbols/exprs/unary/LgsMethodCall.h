#ifndef LOGOSMETHODCALL_H
#define LOGOSMETHODCALL_H
#include "stmts/LgsStmt.h"
#include "LogosUnaryExpr.h"

class LgsMethodCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    LgsMethodImpl* methodImpl = nullptr;
    Position position = Position();

    explicit LgsMethodCall(const string& name) : name(name) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsMethodCall() override;
};



#endif //LOGOSMETHODCALL_H

#ifndef LOGOSMETHODCALL_H
#define LOGOSMETHODCALL_H
#include <stmts/LogosStmt.h>
#include "LogosUnaryExpr.h"

class LogosMethodCall final : public LogosStmt, public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    Position position = Position();

    explicit LogosMethodCall(const string& name) : name(name) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LogosMethodCall() override;
};



#endif //LOGOSMETHODCALL_H

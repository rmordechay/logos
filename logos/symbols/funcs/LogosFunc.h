#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "CodeGeneration.h"
#include "stmts/LogosVarDec.h"
#include "types/LogosType.h"

class LogosFunc : public CodeGeneration {
public:
    string name;
    LogosType* type;
    vector<LogosVarDec*> params;
    vector<LogosStmt*> stmts;

    explicit LogosFunc(const string& name, LogosType* funcType) : name(name), type(funcType) {}
    ~LogosFunc() override;
};

inline LogosFunc::~LogosFunc() {
    for (const auto param : params) {
        delete param;
    }
    for (const auto stmt : stmts) {
        delete stmt;
    }
}

#endif //LOGOSFUNC_H

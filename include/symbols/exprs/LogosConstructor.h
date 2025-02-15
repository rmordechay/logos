#ifndef LOGOSCONSTRUCTOREXPR_H
#define LOGOSCONSTRUCTOREXPR_H
#include "LogosUnaryExpr.h"
#include <llvm/IR/Module.h>

class LogosConstructor final : public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    LogosObject* obj = nullptr;

    explicit LogosConstructor(const string& name) : name(name) {}
    string getName() override;
    LogosSymbolType getSymbolType() override;
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    LogosConstructor* asConstructor() override;
    ~LogosConstructor() override = default;
};



#endif //LOGOSCONSTRUCTOREXPR_H

#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LogosUnaryExpr.h"
#include <llvm/IR/Module.h>

class LogosInstance final : public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    LogosObject* obj = nullptr;

    explicit LogosInstance(const string& name) : name(name) {}
    string getName() override;
    LogosSymbolType getSymbolType() override;
    Value* computeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosInstance() override = default;
};



#endif //LOGOSINSTANCE_H

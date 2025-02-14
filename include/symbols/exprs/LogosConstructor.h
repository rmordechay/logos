#ifndef LOGOSCONSTRUCTOREXPR_H
#define LOGOSCONSTRUCTOREXPR_H
#include "LogosUnaryExpr.h"
#include <llvm/IR/Module.h>

class LogosConstructor final : public LogosUnaryExpr {
public:
    std::string name;
    vector<LogosExpr*> args;

    explicit LogosConstructor(const string& name) : name(name) {}
    Value* writeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosConstructor() override = default;
};



#endif //LOGOSCONSTRUCTOREXPR_H

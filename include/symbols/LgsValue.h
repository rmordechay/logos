#ifndef CODEGENERATION_H
#define CODEGENERATION_H
#include "LgsLocation.h"
#include <Token.h>
#include <json/json.hpp>
#include <llvm/IR/Value.h>

class LgsRuntime;
class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    BasicBlock* createBasicBlock(const char* name) const;
    void startBlock(BasicBlock* block, Function* IRFunc) const;
    void startBlockFunc(LgsRuntime* runtime, LgsFunc* currentFunc) const;
    Value* hashIRValue(LgsRuntime* runtime, Value* value) const;
    virtual std::string format(std::string& indentStr);
    virtual void setLocation(const antlr4::Token* ctx);
    virtual nlohmann::json asJSON();
    virtual ~LgsValue() = default;
};

#endif //CODEGENERATION_H

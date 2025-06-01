#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include "LgsLocation.h"
#include <Token.h>
#include <json/json.hpp>
#include <llvm/IR/Value.h>

using namespace llvm;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    BasicBlock* createBasicBlock(const char* name) const;
    void startBlock(Module* module, BasicBlock* block) const;
    void startBlockFunc(Module* module) const;
    Value* hashIRValue(Module* module, Value* value) const;
    virtual std::string format(std::string& indentStr);
    virtual void setLocation(const antlr4::Token* ctx);
    virtual nlohmann::json asJSON();
    virtual ~LgsValue() = default;
};

#endif //CODEGENERATION_H

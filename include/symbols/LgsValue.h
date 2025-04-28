#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <Token.h>
#include <llvm/IR/Value.h>
#include "CodeGenMetadata.h"

#include <json/json.hpp>

struct CodeGenMetadata;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;
    bool isFreed = false;

    void setIRValue(Value* value);
    GlobalVariable* createIRGlobal(Module* module, Constant* strConstant) const;
    BasicBlock* createBasicBlock(const char* name) const;
    void startBlock(CodeGenMetadata* metadata, BasicBlock* block) const;
    Value* createIRStr(Module* module, const std::string& value) const;
    Value* hashIRValue(CodeGenMetadata* metadata, Value* value) const;
    virtual string format(string& indentStr);
    virtual void setLocation(const antlr4::Token* ctx);
    virtual void free(CodeGenMetadata* metadata);
    virtual json asJSON();
    virtual ~LgsValue() = default;
};

#endif //CODEGENERATION_H

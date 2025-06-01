#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include "codegen/CodegenMetadata.h"
#include <Token.h>
#include <llvm/IR/Value.h>
#include <json/json.hpp>

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    BasicBlock* createBasicBlock(const char* name) const;
    void startBlock(CodegenMetadata* metadata, BasicBlock* block) const;
    void startBlockFunc(CodegenMetadata* metadata) const;
    Value* getIRStr(Module* module, const std::string& value) const;
    Value* hashIRValue(CodegenMetadata* metadata, Value* value) const;
    virtual string format(string& indentStr);
    virtual void setLocation(const antlr4::Token* ctx);
    virtual json asJSON();
    virtual ~LgsValue() = default;
};

#endif //CODEGENERATION_H

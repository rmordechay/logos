#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <Token.h>
#include <llvm/IR/Value.h>
#include "CodeGenMetadata.h"
#include "LgsData.h"

struct CodeGenMetadata;

struct Location {
    size_t lineNumber{};
    size_t posInLine{};
};

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    GlobalVariable* createIRGlobal(Module* module, Constant* strConstant) const;
    BasicBlock* createBasicBlock(const char* name) const;
    void startBlock(CodeGenMetadata* metadata, BasicBlock* block, bool enterScope = false) const;
    virtual void setLocation(const antlr4::Token* ctx);
    virtual json asJson();
    virtual void free(CodeGenMetadata* metadata);
    virtual ~LgsValue() = default;
};

#endif //CODEGENERATION_H

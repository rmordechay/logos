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

    void setIRValue(Value* value);
    Value* getIRValue(CodeGenMetadata* metadata);
    GlobalVariable* createIRGlobal(Module* module, Constant* strConstant) const;
    virtual void setLocation(const antlr4::Token* ctx);
    virtual json asJson();
    static BasicBlock* createBasicBlock(const char* name);
    static void startBlock(CodeGenMetadata* metadata, BasicBlock* block, bool enterScope = false);
    virtual ~LgsValue() = default;
private:
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    Value* IRValue = nullptr;
};

#endif //CODEGENERATION_H

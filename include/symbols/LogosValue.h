#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include "codegen/LogosMetadata.h"

#include <llvm/IR/IRBuilder.h>
#include <Token.h>

using namespace llvm;
using namespace std;

class LogosValue {
public:
    Position position = Position();
    Value* getIRValue(CodeGenMetadata* metadata);
    void setIRValue(Value* value);
    virtual void setPosition(const antlr4::Token* ctx, const string& filePath);
    virtual ~LogosValue() = default;
protected:
    virtual Value *computeIRValue(CodeGenMetadata* metadata) = 0;
private:
    Value* IRValue = nullptr;
};

inline void LogosValue::setPosition(const antlr4::Token* ctx, const string& filePath) {
    position.lineNumber = ctx->getLine();
    position.posInLine = ctx->getCharPositionInLine();
    position.filePath = &filePath;
}

inline Value* LogosValue::getIRValue(CodeGenMetadata* metadata) {
    if (!IRValue) {
        IRValue = computeIRValue(metadata);
    }
    return IRValue;
}

inline void LogosValue::setIRValue(Value* value) {
    IRValue = value;
}

#endif //CODEGENERATION_H

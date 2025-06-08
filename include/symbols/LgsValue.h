#pragma once

class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    BasicBlock* createBasicBlock(const char* name, LLVMContext& context) const;
    void startBlock(LgsRuntime* runtime, BasicBlock* block) const;
    void startBlockFunc(LgsRuntime* runtime) const;
    Value* hashIRValue(LgsRuntime* runtime, Value* value) const;
    virtual std::string format(std::string& indentStr);
    virtual void setLocation(const antlr4::Token* ctx);
    virtual nlohmann::json asJSON();
    virtual ~LgsValue() = default;
};



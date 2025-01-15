#ifndef CODENODE_H
#define CODENODE_H

#include "StackFrame.h"

#include <map>
#include <stack>
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosExpr.h"
#include <llvm/IR/IRBuilder.h>
#include "ExprHelper.h"

using namespace llvm;

class CodeNode {
public:
    LLVMContext* context = nullptr;
    IRBuilder<>* builder = nullptr;
    Module* module = nullptr;

    void init(LLVMContext* context, IRBuilder<>* builder, Module* module) {
        this->context = context;
        this->builder = builder;
        this->module = module;
    }
    virtual void generateCode(RuntimeStackFrame* stackFrame) = 0;
    virtual ~CodeNode() = default ;
};

#endif //CODENODE_H

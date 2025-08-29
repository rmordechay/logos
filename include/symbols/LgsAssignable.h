#pragma once

class LgsExpr;
class LgsLLVMGen;

class LgsAssignable {
public:
    virtual void assign(LgsLLVMGen& cg, LgsExpr* expr) = 0;
    virtual ~LgsAssignable() = default;
};

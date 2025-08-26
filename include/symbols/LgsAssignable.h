#pragma once

class LgsExpr;
class LgsLLVM;

class LgsAssignable {
public:
    virtual void assign(LgsLLVM& codeGen, LgsExpr* expr) = 0;
    virtual ~LgsAssignable() = default;
};

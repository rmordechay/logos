#ifndef CODEGENNODE_H
#define CODEGENNODE_H
#include "LogosSymbol.h"

class CodeNode {
public:
    LogosSymbol *left;
    LogosSymbol *right;
    virtual ~CodeNode() = default;
    virtual void generateCode() const;
protected:
    explicit CodeNode(LogosSymbol *left, LogosSymbol *right): left(left), right(right) {}
};

class StoreInt final : public CodeNode {
public:
    explicit StoreInt(LogosSymbol *left): CodeNode(left, nullptr) {}
    void generateCode() const override {

    }
};

class Add final : public CodeNode {
public:
    explicit Add(LogosSymbol *left, LogosSymbol *right): CodeNode(left, right) {}
    void generateCode() const override {

    }
};

#endif //CODEGENNODE_H

#ifndef CODEGENNODE_H
#define CODEGENNODE_H
#include "LogosSymbol.h"

enum Command {
    CMD_NOOP,
    CMD_STORE,
    CMD_LOAD,
    CMD_ADD,
};

class ASTNode {
public:
    LogosSymbol *left;
    LogosSymbol *right;
    explicit ASTNode(LogosSymbol *left, LogosSymbol *right): left(left), right(right) {}
    virtual ~ASTNode() = default;
    virtual void generateCode() const;
};

class LogosInteger final : public ASTNode {
public:
    explicit LogosInteger(LogosSymbol *left): ASTNode(left, nullptr) {}
    void generateCode() const override {

    }
};

class LogosAdd final : public ASTNode {
public:
    explicit LogosAdd(LogosSymbol *left, LogosSymbol *right): ASTNode(left, right) {}
    void generateCode() const override {

    }
};

#endif //CODEGENNODE_H

#pragma once
#include "LgsValue.h"

class LgsReturn;
class LgsStmt;
class LgsObject;

class LgsStmtWrapper {
public:
    enum class Type { Object, Stmt, Expr };
    Type type;
    union {
        LgsObject* obj;
        LgsStmt* stmt;
        LgsExpr* expr;
    };
    explicit LgsStmtWrapper(LgsObject* o) : type(Type::Object), obj(o) {}
    explicit LgsStmtWrapper(LgsStmt* s) : type(Type::Stmt), stmt(s) {}
    explicit LgsStmtWrapper(LgsExpr* e) : type(Type::Expr), expr(e) {}
    bool isTerminator() const;
};

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmtWrapper> stmts;
    LgsReturn* returnStmt = nullptr;
    bool isMacro = false;

    explicit LgsStmtsBlock(const std::vector<LgsStmtWrapper>& stmts = {}) : stmts(stmts) {}
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsStmtsBlock() override;
};

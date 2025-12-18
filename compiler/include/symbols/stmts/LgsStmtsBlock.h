#pragma once
#include "LgsValue.h"

class LgsReturn;
class LgsStmt;
class LgsObject;

class LgsStmtWrapper {
public:
    enum class WrapperType { Object, Stmt, Expr };
    WrapperType wrapperType = WrapperType::Stmt;
    union {
        LgsStmt* stmt;
        LgsExpr* expr;
        LgsObject* obj;
    };

    LgsStmtWrapper() = default;
    explicit LgsStmtWrapper(LgsStmt* s) : stmt(s) {}
    explicit LgsStmtWrapper(LgsObject* o) : wrapperType(WrapperType::Object), obj(o) {}
    explicit LgsStmtWrapper(LgsExpr* e) : wrapperType(WrapperType::Expr), expr(e) {}
    bool isTerminator() const;
    LgsStmtWrapper clone() const;
};

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmtWrapper> stmts;
    bool isMacro = false;
    bool isSingleLine = false;

    explicit LgsStmtsBlock(const std::vector<LgsStmtWrapper>& stmts = {}) : stmts(stmts) {}
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCgModule& cg) override;
    LgsStmtsBlock* clone() const;
    ~LgsStmtsBlock() override;
};

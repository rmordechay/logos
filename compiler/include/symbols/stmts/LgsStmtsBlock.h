#pragma once
#include <vector>
#include "LgsValue.h"


class LgsReturn;
class LgsStmt;
class LgsObject;
class LgsExpr;
class LgsFunc;

class LgsStmtWrapper {
public:
    enum class WrapperType { Stmt, Expr, Object };
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
};

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmtWrapper> stmts;
    bool isMacro = false;

    explicit LgsStmtsBlock(const std::vector<LgsStmtWrapper>& stmts = {}) : stmts(stmts) {}
    LgsFunc* wrapBlockInFunc();
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsStmtsBlock* clone() const override;
    ~LgsStmtsBlock() override;
};

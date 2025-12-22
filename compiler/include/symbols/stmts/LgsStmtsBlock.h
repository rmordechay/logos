#pragma once
#include "LgsValue.h"
#include "types/LgsGenericType.h"

class LgsReturn;
class LgsStmt;
class LgsObject;

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
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCgModule& cg) override;
    LgsStmtsBlock* clone() override;
    ~LgsStmtsBlock() override;
};

#pragma once
#include "LgsBreak.h"
#include "LgsContinue.h"
#include "LgsReturn.h"
#include "exprs/LgsSelection.h"
#include "stmts/LgsStmt.h"
#include "types/LgsObject.h"

namespace llvm {
    class BasicBlock;
}

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
    bool isTerminator() const {
        switch (type) {
        case Type::Stmt: {
            const bool isControlFlow = dynamic_cast<LgsBreak*>(stmt) || dynamic_cast<LgsContinue*>(stmt) || dynamic_cast<LgsReturn*>(stmt);
            if (isControlFlow) return true;
            break;
        }
        case Type::Expr: {
            const auto fc = expr->asFuncCall();
            if (fc && fc->func && fc->func->funcType->isTerminator) return true;
            const auto selection = expr->asSelection();
            if (!selection) break;
            const auto methodCall = selection->asMethodCall();
            if (!methodCall) break;
            return methodCall->func && methodCall->func->funcType->isTerminator;
        }
        case Type::Object:
            break;
        }
        return false;
    }
};

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmtWrapper> stmts;
    LgsReturn* returnStmt = nullptr;
    bool isMacro = false;

    explicit LgsStmtsBlock(const std::vector<LgsStmtWrapper>& stmts = {}) : stmts(stmts) {}
    void hashNode(size_t& oldHash) override;
    ~LgsStmtsBlock() override;
};

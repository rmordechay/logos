#pragma once
#include "LgsStmt.h"

class LgsArrayExpr;
class LgsHashMap;
struct LgsIndex;
class LgsIterIndex;
class LgsType;
class LgsBinaryExpr;
class LgsExpr;


class LgsAssignment final : public LgsStmt {
public:
    LgsExpr* left = nullptr;
    LgsExpr* right = nullptr;
    LgsBinaryExpr* binaryExpr = nullptr;

    explicit LgsAssignment(LgsBinaryExpr* binaryExpr) : binaryExpr(binaryExpr) {}
    explicit LgsAssignment(LgsExpr* left, LgsExpr* right) : left(left), right(right) {}
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsAssignment() override;
};

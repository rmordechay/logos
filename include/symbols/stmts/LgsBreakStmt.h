#ifndef LGSBREAK_H
#define LGSBREAK_H
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreakStmt final : public LgsStmt {
public:
    bool breakIfStmt = false;

    explicit LgsBreakStmt(const bool breakIfStmt) : breakIfStmt(breakIfStmt) {}
    void createIRStmt(LgsRuntime* runtime) override;
    ~LgsBreakStmt() override = default;
};


#endif //LGSBREAK_H

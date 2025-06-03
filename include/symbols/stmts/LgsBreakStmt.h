#ifndef LGSBREAK_H
#define LGSBREAK_H
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreakStmt final : public LgsStmt {
public:
    void createIRStmt(LgsRuntime* runtime) override;
    ~LgsBreakStmt() override = default;
};


#endif //LGSBREAK_H

#ifndef LGSCONTINUE_H
#define LGSCONTINUE_H
#include "LgsStmt.h"

class LgsContinueStmt final : public LgsStmt {
public:
    void createIRStmt(Module* module, LgsRuntime* runtime) override;
    ~LgsContinueStmt() override = default;
};


#endif //LGSCONTINUE_H

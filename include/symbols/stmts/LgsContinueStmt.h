#ifndef LGSCONTINUE_H
#define LGSCONTINUE_H
#include "LgsStmt.h"

class LgsContinueStmt final : public LgsStmt {
public:
    void createIRStmt(CodeGenMetadata* metadata) override;
    ~LgsContinueStmt() override = default;
};


#endif //LGSCONTINUE_H

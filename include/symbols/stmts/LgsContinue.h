#ifndef LGSCONTINUE_H
#define LGSCONTINUE_H
#include "LgsStmt.h"

class LgsContinue final : public LgsStmt {
public:
    void createIRStmt(CodeGenMetadata* metadata) override;
    ~LgsContinue() override = default;
};


#endif //LGSCONTINUE_H

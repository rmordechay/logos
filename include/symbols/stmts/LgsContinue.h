#ifndef LGSCONTINUE_H
#define LGSCONTINUE_H
#include "LgsStmt.h"

class LgsContinue final : public LgsStmt {
public:
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsContinue() override = default;
};


#endif //LGSCONTINUE_H

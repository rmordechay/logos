#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include <LgsValue.h>

class LgsStmt : virtual public LgsValue {
public:
    virtual Value* createIRValue(CodeGenMetadata* metadata) = 0;
    ~LgsStmt() override = default;
};

#endif //LOGOSSTMT_H

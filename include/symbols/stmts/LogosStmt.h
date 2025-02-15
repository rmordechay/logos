#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include "CodeGeneration.h"

class LogosStmt : virtual public CodeGeneration {
public:
    virtual ~LogosStmt() override = default;
};

#endif //LOGOSSTMT_H

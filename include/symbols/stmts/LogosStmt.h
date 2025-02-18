#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include <LogosValue.h>

class LogosStmt : virtual public LogosValue {
public:
    ~LogosStmt() override = default;
};

#endif //LOGOSSTMT_H

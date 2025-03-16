#ifndef LOGOSSTMT_H
#define LOGOSSTMT_H
#include <LgsValue.h>

class LgsStmt : virtual public LgsValue {
public:
    ~LgsStmt() override = default;
};

#endif //LOGOSSTMT_H

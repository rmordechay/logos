#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

using namespace llvm;
using namespace std;
class LogosConstant;

class LogosType {
public:
    virtual const string name() const = 0;
    virtual Type* getIRType() = 0;
    virtual LogosConstant* getZeroValue() = 0;
    virtual bool operator==(LogosType* other) const = 0;
    virtual ~LogosType() = default;
};

#endif //LOGOSTYPE_H

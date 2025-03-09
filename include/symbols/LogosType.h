#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

using namespace llvm;
using namespace std;
class LogosConstant;

class LogosType {
public:
    virtual const string getName() const = 0;
    virtual Type* getIRType() = 0;
    virtual LogosConstant* getZeroValue() = 0;
    virtual bool equals(LogosType* other) const = 0;
    bool operator==(LogosType* other) const;
    bool operator!=(LogosType* other) const;
    virtual ~LogosType() = default;
};

inline bool LogosType::operator==(LogosType* other) const {
    return equals(other);
}

inline bool LogosType::operator!=(LogosType* other) const {
    return !equals(other);
}

#endif //LOGOSTYPE_H

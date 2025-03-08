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
    virtual bool equals(LogosType* other) const = 0;
    virtual ~LogosType() = default;
    bool operator==(LogosType* other) const;
    bool operator!=(LogosType* other) const;
};

inline bool LogosType::operator==(LogosType* other) const {
    return equals(other);
}

inline bool LogosType::operator!=(LogosType* other) const {
    return !equals(other);
}

#endif //LOGOSTYPE_H

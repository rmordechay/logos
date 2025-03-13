#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <string>
#include <llvm/IR/Type.h>
#include <map>

using namespace std;
using namespace llvm;

class LogosConstant;
class LogosField;
class LogosMethodImpl;

class LogosType {
public:
    map<string, LogosField*> fields;
    map<string, LogosMethodImpl*> methods;

    LogosField* getField(const string& name);
    LogosMethodImpl* getMethod(const string& name);
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

inline LogosField* LogosType::getField(const string& name) {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

inline LogosMethodImpl* LogosType::getMethod(const string& name) {
    const auto it = methods.find(name);
    if (it != methods.end()) {
        return it->second;
    }
    return nullptr;
}

#endif //LOGOSTYPE_H

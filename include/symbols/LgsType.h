#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <string>
#include <llvm/IR/Type.h>
#include <map>

using namespace std;
using namespace llvm;

class LgsConst;
class LgsField;
class LgsMethodImpl;

class LgsType {
public:
    map<string, LgsField*> fields;
    map<string, LgsMethodImpl*> methods;

    LgsField* getField(const string& name);
    LgsMethodImpl* getMethod(const string& name);
    virtual const string getName() const = 0;
    virtual Type* getIRType() = 0;
    virtual LgsConst* getZeroValue() = 0;
    virtual bool equals(LgsType* other) const = 0;
    virtual LgsType* inferBinaryType(LgsType* other) const = 0;
    virtual ~LgsType() = default;
};

inline LgsField* LgsType::getField(const string& name) {
    const auto it = fields.find(name);
    if (it != fields.end()) {
        return it->second;
    }
    return nullptr;
}

inline LgsMethodImpl* LgsType::getMethod(const string& name) {
    const auto it = methods.find(name);
    if (it != methods.end()) {
        return it->second;
    }
    return nullptr;
}

#endif //LOGOSTYPE_H

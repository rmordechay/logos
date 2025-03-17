#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <string>
#include <map>
#include <llvm/IR/Type.h>

using namespace std;
using namespace llvm;

class LgsConst;
class LgsField;
class LgsMethodImpl;

class LgsType {
public:
    // TODO make values const
    map<string, LgsField*> fields;
    map<string, LgsMethodImpl*> methods;

    LgsField* getField(const string& name);
    LgsMethodImpl* getMethod(const string& name);
    virtual const string getName() const = 0;
    virtual Type* getIRType() = 0;
    virtual LgsConst* getZeroValue() = 0;
    virtual bool equals(LgsType* other) const = 0;
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual ~LgsType() = default;
};

#endif //LOGOSTYPE_H

#ifndef LOGOSVOID_H
#define LOGOSVOID_H

#include "LogosType.h"
#include <LogosMetadata.h>

using namespace std;

class LogosVoid final : public LogosType {
public:
    Type* IRType = Type::getVoidTy(context);
    string typeName = "Void";

    const string getName() const override;
    Type* getIRType() override;
    LogosConstant* getZeroValue() override;
    bool equals(LogosType* other) const override;
    LogosField* getField(const string& name) override;
    LogosMethodImpl* getMethod(const string& name) override;
    ~LogosVoid() override = default;
};

inline LogosVoid LOGOS_VOID;

#endif //LOGOSVOID_H

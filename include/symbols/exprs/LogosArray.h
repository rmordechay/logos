#ifndef LOGOSARRAY_H
#define LOGOSARRAY_H

#include "LogosValue.h"

class LogosArray final : public LogosValue {
public:
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosArray() override = default;
};



#endif //LOGOSARRAY_H

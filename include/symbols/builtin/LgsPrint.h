#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "exprs/unary/constants/LgsCharConst.h"
#include "funcs/LgsFuncImpl.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/str/LgsStr.h"
#include <types/primitives/LgsVoid.h>

class LgsPrint final : public LgsFuncImpl {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(const vector<LgsParam*>& params): LgsFuncImpl(name, &LGS_VOID) {
        funcType.params = params;
    }
    void setIRFuncType(const CodeGenMetadata* metadata);
    ~LgsPrint() override = default;
};

inline LgsPrint lgsPrintInt({new LgsParam(&LGS_INT)});
inline LgsPrint lgsPrintFloat({new LgsParam(&LGS_FLOAT)});
inline LgsPrint lgsPrintChar({new LgsParam(&LGS_CHAR)});
inline LgsPrint lgsPrintBool({new LgsParam(&LGS_BOOL)});
inline LgsPrint lgsPrintStr({new LgsParam(new LgsStr())});

#endif //LOGOSPRINT_H

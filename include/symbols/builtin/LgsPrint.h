#ifndef LOGOSPRINT_H
#define LOGOSPRINT_H
#include "LgsBuiltinMethod.h"
#include "funcs/LgsFuncImpl.h"
#include "types/primitives/LgsBool.h"
#include "utils/LgsUtils.h"

#include <types/primitives/LgsVoid.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "print";
    LgsParam input{&LGS_ANY};
    LgsParam args{&LGS_ANY};

    explicit LgsPrint(): LgsBuiltinFunc(name, &LGS_VOID) {
        funcType.isVariadic = true;
        funcType.IRName = "printf";
        funcType.params = {&input, &args};
    }

    Value* call(Module* module, const vector<LgsExpr*>& args) override {
        vector<Value*> IRArgs;
        stringstream str;
        for (int i = 0; i < args.size(); ++i) {
            const auto arg = args[i];
            addIRArg(module, IRArgs, arg);
            str << arg->type->getStrFormatPart() << std::endl;
        }
        IRArgs.insert(IRArgs.begin(), getIRStr(module, str.str()));
        const auto printfFunc = getPrintf(module);
        builder.CreateCall(printfFunc, IRArgs);
        return nullptr;
    }

    ~LgsPrint() override = default;
};

inline LgsPrint lgsPrint;

#endif //LOGOSPRINT_H

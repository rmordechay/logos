#ifndef LGSSTRMETHODS_H
#define LGSSTRMETHODS_H
#include "utils/LgsUtils.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsInt.h"

#define BUFFER_SIZE 1024


class LgsStrFormatFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam args{&LGS_ANY};

    explicit LgsStrFormatFunc(LgsType* parent) : LgsMethodImpl("format", parent->getIRName(), parent) {
        self.type = parent;
        funcType.isVariadic = true;
        funcType.isPublic = true;
        funcType.params = {&self};
    }

    Value* call(Module* module, const vector<LgsExpr*>& args) override {
        const bool isConst = args[0]->type->isConst;
        if (!isConst) assert(false);
        const auto formatString = getFormatString(args);
        const auto baseIRStr = getIRStr(module, formatString);
        const auto bufferType = ArrayType::get(i8Ty, BUFFER_SIZE);
        const auto buffer = builder.CreateAlloca(bufferType);
        const auto gep = builder.CreateGEP(bufferType, buffer, {i32Zero, i32Zero});
        vector<Value*> IRArgs = {gep, builder.getInt64(BUFFER_SIZE), baseIRStr};
        for (int i = 1; i < args.size(); ++i) {
            IRArgs.emplace_back(args[i]->getIRValue(module));
        }
        const auto printfFunc = getSnprintf(module);
        builder.CreateCall(printfFunc, IRArgs);
        return gep;
    }
};


class LgsStrLenFunc final : public LgsMethodImpl {
public:
    LgsParam self{};

    explicit LgsStrLenFunc(LgsType* parent) : LgsMethodImpl("len", parent->getIRName(), &LGS_INT) {
        self.type = parent;
        funcType.IRName = "strlen";
        funcType.params = {&self};
        funcType.isPublic = true;
    }
};

#endif //LGSSTRMETHODS_H

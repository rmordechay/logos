#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsIterable.h"

class LgsStrFormatFunc final : public LgsBuiltinFunc {
public:
    explicit LgsStrFormatFunc(LgsType* parent) : LgsBuiltinFunc("format", parent, parent->getIRName()) {
        funcType.isPublic = true;
        funcType.isVariadic = true;
        funcType.params = {LgsParam{parent}, LgsParam{&LGS_ANY}};
    }

    Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args) override {
        const bool isConst = args[0]->type->isConst;
        if (!isConst) assert(false);
        constexpr auto bufferSize = 1024;
        const auto formatString = getFormatString(args);
        const auto baseIRStr = getIRStr(runtime, formatString);
        const auto bufferType = ArrayType::get(runtime->builder.getInt8Ty(), bufferSize);
        const auto buffer = runtime->builder.CreateAlloca(bufferType);
        const auto gep = runtime->builder.CreateGEP(bufferType, buffer, {runtime->builder.getInt32(0), runtime->builder.getInt32(0)});
        vector<Value*> IRArgs = {gep, runtime->builder.getInt64(bufferSize), baseIRStr};
        for (int i = 1; i < args.size(); ++i) {
            IRArgs.emplace_back(args[i]->getIRValue(runtime));
        }
        const auto printfFunc = getSnprintf(runtime);
        runtime->builder.CreateCall(printfFunc, IRArgs);
        return gep;
    }
};

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc format{this};
    LgsBuiltinFunc len{"len", &LGS_INT, name, {this}};
    LgsBuiltinFunc isEmpty{"isEmpty", &LGS_INT, name, {this}};
    LgsBuiltinFunc isNotEmpty{"isNotEmpty", &LGS_INT, name, {this}};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&format);
        addMethod(&len);
        addMethod(&isEmpty);
        addMethod(&isNotEmpty);
        unpackLength = 1;
    }
    static uint32_t hashString(const string& str);
    size_t getSizeBytes() override;
    string getIRName() override;
    Type* getIRType() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getStrFormatPart() const override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    ~LgsStr() override = default;
};

inline LgsStr LGS_STR;
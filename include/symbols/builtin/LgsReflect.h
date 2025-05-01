#ifndef LGSREFLECT_H
#define LGSREFLECT_H
#include "exprs/unary/LgsArray.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

class LgsReflectGetFields final : public LgsMethodImpl {
public:
    LgsArrayType rt = LgsArrayType(&LGS_STR);
    const LgsObject* parent;

    explicit LgsReflectGetFields(const LgsObject* parent) : LgsMethodImpl("getFields", &rt, parent->name, {LgsParam(new LgsObject())}), parent(parent) {
        isPublic = true;
        isStatic = true;
    }

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        const auto arg = args[1]->asVariable();
        for (const auto& field : arg->type->fields) {
            std::cout << field.first << '\n';
        }
        return nullptr;
    }

    ~LgsReflectGetFields() override = default;
};

class LgsReflect final : public LgsObject {
public:
    static constexpr auto name = "Reflect";
    LgsReflectGetFields getFieldsFunc = LgsReflectGetFields(this);

    explicit LgsReflect() : LgsObject(name) {
        addMethod(&getFieldsFunc);
    }
    ~LgsReflect() override = default;
};

#endif //LGSREFLECT_H

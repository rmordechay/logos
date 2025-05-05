#ifndef LGSMAP_H
#define LGSMAP_H
#include "LgsAny.h"
#include "LgsIterable.h"
#include "LgsPair.h"
#include "LgsVoid.h"
#include "funcs/LgsMethodImpl.h"

class LgsMapInsertFunc final : public LgsMethodImpl {
public:
    LgsParam mapParam = LgsParam();
    LgsParam keyParam = LgsParam(&LGS_ANY);
    LgsParam valueParam = LgsParam(&LGS_ANY);

    explicit LgsMapInsertFunc(LgsType* parent) {
        mapParam.type = parent;
        methodType.name = "insert";
        methodType.rt = &LGS_VOID;
        methodType.parentName = parentName;
        methodType.parentName = parent->getIRName();
        methodType.params = {&mapParam, &keyParam, &valueParam};
    }
};

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsPair underlyingType;
    LgsMapInsertFunc insertFunc = LgsMapInsertFunc(this);

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : LgsIterable(&underlyingType) {
        underlyingType.key = keyType;
        underlyingType.value = valueType;
    }
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool isIndexable(LgsType* indexType) override;
    LgsType* getUnderlyingType() override;
    ~LgsMap() override = default;
};

#endif //LGSMAP_H

#pragma once
#include <utility>
#include "LgsType.h"

class LgsGenericParam;
class LgsInstance;
class LgsLLVMGen;
class LgsField;
class LgsIOPair;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> implements;
    std::vector<LgsGenericParam*> generics;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsIOPair*> ioPairs;
    LgsInstance* singleton = nullptr;
    bool hasGenerics = false;

    explicit LgsObject(std::string  name) : name(std::move(name)) {
        isHeapAlloc = true;
        passByRef = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getName() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    LgsObject* clone() override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    ~LgsObject() override;
};

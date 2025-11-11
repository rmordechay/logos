#include "analysis/LgsTypeResolver.h"
#include "exprs/LgsVariable.h"
#include "files/LgsFile.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsApp.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsEnum.h"
#include "types/LgsFuncType.h"
#include "types/LgsGenericType.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsIterable.h"
#include "types/LgsNullable.h"
#include "types/LgsSubType.h"
#include "utils/LgsErrHandler.h"

bool LgsTypeResolver::resolveGlobals(const std::vector<LgsFile*>& srcFiles, ThreadPool& pool) {
    std::atomic successful = true;
    for (const auto& file : srcFiles) {
        pool.runTask([this, file, &successful] {
            if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
                resolveMainFileTypes(mainFile);
            } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
                resolveObjTypes(objFile->obj, *objFile);
            } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
                resolveInterfaceTypes(interfaceFile->interface, *interfaceFile);
            }
            if (!errHandler.successful) {
                successful.store(false, std::memory_order_relaxed);
            }
        });
    }
    pool.wait();
    errHandler.successful = successful;
    return successful;
}

LgsType* LgsTypeResolver::resolveType(LgsType* type, LgsFile* file) {
    if (const auto nullable = type->asNullable()) {
        nullable->baseType = resolveType(nullable->baseType, file);
    } else if (const auto iterable = type->asIterable()) {
        iterable->baseType = resolveType(iterable->baseType, file);
        rtTypesRegistry.push_back(iterable);
    } else if (const auto pair = type->asPair()) {
        pair->key = resolveType(pair->key, file);
        pair->value = resolveType(pair->value, file);
    } else if (const auto funcType = type->asFuncType()) {
        resolveFuncTypes(funcType, *file);
    }
    if (type->isUnknown()) {
        auto typeName = type->getName();
        auto symbol = globals.table.getSymbol(typeName);
        if (!symbol) {
            symbol = file->symbolTable.getSymbol(typeName);
        }
        if (!symbol) {
            errHandler.addError(E10006, &type->location, file->path, {typeName});
            return type;
        }
        LgsType* newType = nullptr;
        switch (symbol->symbolType) {
        case FUNC:
            newType = symbol->func->funcType->clone();
            break;
        case OBJECT:
            newType = symbol->object->clone();
            break;
        case INTERFACE:
            newType = symbol->interface->clone();
            break;
        case ENUM:
            newType = symbol->enum_->clone();
            break;
        case SUBTYPE:
            newType = symbol->subtype->clone();
            break;
        case GENERIC:
            newType = symbol->generic->clone();
            break;
        case VAR_DEC:
        case PARAM:
        case FIELD:
        case UNKNOWN:
            break;
        }
        assert(newType);
        freeType(type);
        type = newType;
    }
    return type;
}

void LgsTypeResolver::resolveMainFileTypes(LgsMainFile* mf) {
    for (const auto object : mf->objects) {
        resolveObjTypes(object, *mf);
    }
    for (const auto interface : mf->interfaces) {
        resolveInterfaceTypes(interface, *mf);
    }
    for (const auto subtype : mf->subtypes) {
        subtype->subtype = resolveType(subtype->subtype, mf);
        subtype->isPrimitive = subtype->subtype->isPrimitive;
    }
    for (const auto& [_, func] : mf->funcs) {
        if (dynamic_cast<LgsMainFunc*>(func)) continue;
        resolveFuncTypes(func->funcType, *mf);
    }
}

void LgsTypeResolver::resolveObjTypes(LgsObject* obj, LgsFile& file) {
    for (auto& interface : obj->implements) {
        interface = resolveType(interface, &file);
    }

    for (const auto generic : obj->generics) {
        file.symbolTable.addSymbol(LgsSymbol(generic), &errHandler, file.path);
    }

    for (const auto& enum_ : obj->enums) {
        file.symbolTable.addSymbol(LgsSymbol(enum_), &errHandler, file.path);
    }

    for (const auto& field : obj->fields) {
        field->setType(resolveType(field->type, &file));
    }

    for (const auto& ioPair : obj->ioPairs) {
        resolveIOPair(ioPair, obj, file);
    }

    for (const auto& [_, method] : obj->methods) {
        method->funcType->rt = resolveType(method->funcType->rt, &file);
        for (auto& param : method->funcType->params) {
            param.setType(resolveType(param.type, &file));
        }
    }
}

void LgsTypeResolver::resolveInterfaceTypes(LgsInterface* interface, LgsFile& file) {
    for (const auto& field : interface->fields) {
        field->setType(resolveType(field->type, &file));
    }
    for (const auto& [_, method] : interface->methods) {
        resolveFuncTypes(method->funcType, file);
    }
    for (auto& i : interface->implements) {
        i = resolveType(i, &file);
    }
}

void LgsTypeResolver::resolveFuncTypes(LgsFuncType* funcType, LgsFile& file) {
    auto resolveTypeOrGeneric = [&](LgsType* type) -> LgsType* {
        if (!type) return &LGS_VOID;
        for (const auto generic : funcType->generics) {
            if (type->equals(generic)) return generic->clone();
        }
        return resolveType(type, &file);
    };
    for (auto& param : funcType->params) {
        param.setType(resolveTypeOrGeneric(param.type));
    }
    funcType->rt = resolveTypeOrGeneric(funcType->rt);
}

void LgsTypeResolver::resolveIOPair(LgsIOPair* ioPair, LgsObject* obj, LgsFile& file) const {
    ioPair->openFunc = obj->getMethod(ioPair->openFuncName);
    ioPair->openFunc->funcType->isIOMember = true;
    if (!ioPair->openFunc) {
        errHandler.addError(E10005, &ioPair->openFunc->location, file.path, {ioPair->openFuncName, obj->pname()});
    }
    ioPair->closeFunc = obj->getMethod(ioPair->closeFuncName);
    ioPair->closeFunc->funcType->isIOMember = true;
    if (!ioPair->closeFunc) {
        errHandler.addError(E10005, &ioPair->closeFunc->location, file.path, {ioPair->closeFuncName, obj->pname()});
    }
}

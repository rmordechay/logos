#include "analysis/LgsTypeResolver.h"

#include "errors/LgsErrHandler.h"
#include "exprs/LgsVariable.h"
#include "files/LgsFile.h"
#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsEnum.h"
#include "types/LgsFuncType.h"
#include "types/LgsGenericType.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsIterable.h"
#include "types/LgsSubType.h"

#include "errors/LgsErrors.h"
#include "types/LgsNullable.h"
#include "types/LgsSelf.h"

void LgsTypeResolver::resolveType(LgsType*& type) {
    if (!type) return;
    for (size_t i = 0; i < type->genericArgs.size(); ++i) {
        resolveType(type->genericArgs[i]);
    }
    if (const auto self = type->asSelf()) {
        self->baseType = currentObj;
        return;
    }
    if (const auto funcType = type->asFuncType()) {
        resolveFuncType(funcType);
    } else if (const auto iterable = type->asIterable()) {
        resolveType(iterable->baseType);
    } else if (const auto nullable = type->asNullable()) {
        if (nullable->baseType) {
            resolveType(nullable->baseType);
            nullable->isHeap = nullable->baseType->isHeap;
            nullable->passByRef = nullable->baseType->passByRef;
        }
    } else if (const auto pair = type->asPair()) {
        resolveType(pair->key);
        resolveType(pair->value);
    }

    if (type->isUnknown()) {
        auto typeName = type->getName();
        const auto newType = findSymbol(typeName);
        if (!newType) {
            errHandler.addError(E10006, &type->location, file->path, {typeName});
            return;
        }
        freeType(type);
        type = newType;
    }
}

void LgsTypeResolver::resolveMainFile(LgsMainFile* mf) {
    for (const auto object : mf->objects) {
        resolveObjTypes(object);
    }
    for (const auto interface : mf->interfaces) {
        resolveInterface(interface);
    }
    for (const auto subtype : mf->subtypes) {
        resolveType(subtype->subtype);
    }
    for (const auto& [_, func] : mf->funcs) {
        if (dynamic_cast<LgsMainFunc*>(func)) continue;
        resolveFuncType(func->funcType);
    }
}

void LgsTypeResolver::resolveObjTypes(LgsObject* obj) {
    currentObj = obj;
    for (auto& interface : obj->implements) {
        if (interface->asSelf()) {
            errHandler.addError(E10014, &interface->location, file->path, {});
        } else {
            resolveType(interface);
        }
    }

    for (const auto generic : obj->generics) {
        if (generic->asSelf()) {
            errHandler.addError(E10014, &generic->location, file->path, {});
        }
    }

    for (const auto& enum_ : obj->enums) {
        file->symbolTable.addSymbol(LgsSymbol(enum_), &errHandler, file->path);
    }

    for (const auto& field : obj->fields) {
        resolveType(field->type);
    }

    for (const auto& [_, method] : obj->methods) {
        resolveType(method->funcType->rt);
        for (auto& param : method->funcType->params) {
            resolveType(param.type);
        }
    }
    currentObj = nullptr;
}

void LgsTypeResolver::resolveInterface(LgsInterface* interface) {
    for (const auto& field : interface->fields) {
        resolveType(field->type);
    }
    for (const auto& [_, method] : interface->methods) {
        resolveFuncType(method->funcType);
    }
}

void LgsTypeResolver::resolveFuncType(LgsFuncType* funcType) {
    assert(funcType);
    const auto oldFunc = currentFuncType;
    currentFuncType = funcType;
    for (auto& param : funcType->params) {
        if (const auto& cb = param.type->asFuncType()) {
            cb->genericTypes = funcType->genericTypes;
        }
        resolveType(param.type);
        if (const auto ft = param.type->asFuncType()) {
            ft->name = param.name;
        }
    }
    resolveType(funcType->rt);
    funcType->swapReturn = !funcType->isExternal && funcType->rt->asSArray();
    currentFuncType = oldFunc;
}

LgsType* LgsTypeResolver::findSymbol(const std::string& typeName) const {
    auto symbol = globals.getSymbol(typeName);
    if (!symbol) {
        symbol = file->symbolTable.getSymbol(typeName);
        if (!symbol) {
            symbol = file->symbolTable.getSymbol(typeName);
        }
    }
    if (symbol) {
        switch (symbol->symbolType) {
        case FUNC: return symbol->func->funcType;
        case OBJECT: return symbol->object;
        case INTERFACE: return symbol->interface;
        case ENUM: return symbol->enum_;
        case SUBTYPE: return symbol->subtype;
        default: break;
        }
    }
    if (currentFuncType) {
        for (const auto genericType : currentFuncType->genericTypes) {
            if (genericType->name == typeName) {
                return genericType;
            }
        }
    }
    return nullptr;
}

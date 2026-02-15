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
        const auto symbol = findSymbol(type->getName(), type->location);
        if (symbol.symbolType == UNKNOWN) return;
        LgsType* newType = nullptr;
        switch (symbol.symbolType) {
        case FUNC:
            newType = symbol.func->funcType;
            break;
        case OBJECT:
            newType = symbol.object;
            break;
        case INTERFACE:
            newType = symbol.interface;
            break;
        case ENUM:
            newType = symbol.enum_;
            break;
        case SUBTYPE:
            newType = symbol.subtype;
            break;
        case GENERIC:
            newType = symbol.generic;
            break;
        default:
            break;
        }
        assert(newType);
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
        } else {
            file->symbolTable.addSymbol(LgsSymbol(generic), &errHandler, file->path);
        }
    }

    for (const auto& enum_ : obj->enums) {
        file->symbolTable.addSymbol(LgsSymbol(enum_), &errHandler, file->path);
    }

    for (const auto& field : obj->fields) {
        resolveType(field->type);
    }

    for (const auto& ioPair : obj->ioPairs) {
        resolveIOPair(ioPair, obj);
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

void LgsTypeResolver::resolveIOPair(LgsIOPair* ioPair, LgsObject* obj) const {
    ioPair->openFunc = obj->getMethod(ioPair->openFuncName);
    ioPair->openFunc->funcType->isIOMember = true;
    if (!ioPair->openFunc) {
        errHandler.addError(E10005, &ioPair->openFunc->location, file->path, {ioPair->openFuncName, obj->pname()});
    }
    ioPair->closeFunc = obj->getMethod(ioPair->closeFuncName);
    ioPair->closeFunc->funcType->isIOMember = true;
    if (!ioPair->closeFunc) {
        errHandler.addError(E10005, &ioPair->closeFunc->location, file->path, {ioPair->closeFuncName, obj->pname()});
    }
}

LgsSymbol LgsTypeResolver::findSymbol(const std::string& typeName, const LgsLocation& location) const {
    if (const auto symbol = globals.getSymbol(typeName)) return *symbol;
    if (const auto symbol = file->symbolTable.getSymbol(typeName)) return *symbol;
    if (currentFuncType) {
        for (const auto genericType : currentFuncType->genericTypes) {
            if (genericType->name == typeName) return LgsSymbol(genericType);
        }
    }
    errHandler.addError(E10006, &location, file->path, {typeName});
    return LgsSymbol();
}

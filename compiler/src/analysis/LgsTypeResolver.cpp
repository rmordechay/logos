#include "analysis/LgsTypeResolver.h"
#include "exprs/LgsVariable.h"
#include "files/LgsFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
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
#include "errors/LgsErrHandler.h"
#include "errors/LgsErrors.h"
#include "types/LgsNullable.h"

void LgsTypeResolver::resolveType(LgsType*& type) {
    if (!type) return;
    for (size_t i = 0; i < type->genericArgs.size(); ++i) {
        resolveType(type->genericArgs[i]);
    }

    if (const auto funcType = type->asFuncType()) {
        resolveFuncType(funcType);
    } else if (const auto iterable = type->asIterable()) {
        if (iterable->genericArgs.empty()) {
            resolveType(iterable->baseType);
        } else {
            iterable->baseType = iterable->genericArgs.front();
        }
    } else if (const auto nullable = type->asNullable()) {
        if (!nullable->isNull) {
            resolveType(nullable->baseType);
            nullable->passByRef = nullable->baseType->passByRef;
            nullable->isHeapAlloc = nullable->baseType->isHeapAlloc;
        }
    } else if (const auto pair = type->asPair()) {
        resolveType(pair->key);
        resolveType(pair->value);
    }

    if (type->isUnknown()) {
        const auto typeName = type->getName();
        const auto symbol = findSymbol(typeName, type->location);
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
}

void LgsTypeResolver::resolveMainFile(LgsMainFile* mf) {
    for (const auto object : mf->objects) {
        resolveObj(object);
    }
    for (const auto interface : mf->interfaces) {
        resolveInterface(interface);
    }
    for (const auto subtype : mf->subtypes) {
        resolveType(subtype->subtype);
        subtype->isPrimitive = subtype->subtype->isPrimitive;
    }
    for (const auto& [_, func] : mf->funcs) {
        if (dynamic_cast<LgsMainFunc*>(func)) continue;
        resolveFuncType(func->funcType);
    }
}

void LgsTypeResolver::resolveObj(LgsObject* obj) {
    for (auto& interface : obj->implements) {
        resolveType(interface);
    }

    for (const auto generic : obj->generics) {
        file->symbolTable.addSymbol(LgsSymbol(generic), &errHandler, file->path);
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
    currentFuncType = funcType;
    for (auto& param : funcType->params) {
        resolveType(param.type);
    }
    resolveType(funcType->rt);
    currentFuncType = nullptr;
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
    auto symbol = globals.table.getSymbol(typeName);
    if (symbol) return *symbol;
    symbol = file->symbolTable.getSymbol(typeName);
    if (symbol) return *symbol;
    for (const auto genericType : currentFuncType->genericTypes) {
        if (genericType->name != typeName) continue;
        return LgsSymbol(genericType);
    }
    errHandler.addError(E10006, &location, file->path, {typeName});
    return LgsSymbol();
}

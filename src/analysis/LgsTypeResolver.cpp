#include "analysis/LgsTypeResolver.h"
#include "files/LgsFile.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsEnum.h"
#include "types/LgsFuncType.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsIterable.h"
#include "types/LgsNullable.h"
#include "types/LgsSubType.h"
#include "utils/LgsErrHandler.h"

bool LgsTypeResolver::resolveGlobalTypes(const std::vector<LgsFile*>& ast, ThreadPool& pool) {
    bool successful = true;
    for (const auto& file : ast) {
        pool.runTask([this, file, &successful] {
            if (const auto mf = dynamic_cast<LgsMainFile*>(file)) {
                resolveMainFileTypes(mf);
            } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
                resolveObjTypes(objFile->obj, *objFile);
            } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
                resolveInterfaceTypes(interfaceFile->interface, *interfaceFile);
            }
            {
                std::lock_guard lock(mtx);
                successful = successful && errHandler.successful;
            }
        });
    }
    pool.wait();
    return successful;
}

LgsType* LgsTypeResolver::resolveType(LgsType* type, LgsFile* file) {
    if (const auto nullable = type->asNullable()) {
        nullable->baseType = resolveType(nullable->baseType, file);
    } else if (const auto iter = type->asIterable()) {
        resolveIterable(iter, *file);
    } else if (const auto pair = type->asPair()) {
        pair->key = resolveType(pair->key, file);
        pair->value = resolveType(pair->value, file);
    } else if (const auto funcType = type->asFuncType()) {
        resolveFuncTypes(funcType, *file);
    }
    if (type->isUnknown()) {
        auto typeName = type->getName();
        auto symbol = globals.getSymbol(typeName);
        if (!symbol) {
            symbol = file->symbolTable.getSymbol(typeName);
        }
        if (!symbol) {
            errHandler.addError(E10006, &type->location, {typeName});
            return nullptr;
        }
        LgsType* newType = nullptr;
        switch (symbol->symbolType) {
        case FUNC:
            newType = symbol->func->funcType;
            break;
        case OBJECT:
            newType = symbol->object;
            break;
        case INTERFACE:
            newType = symbol->interface;
            break;
        case GROUP:
            newType = symbol->group;
            break;
        case ENUM:
            newType = symbol->enum_;
            break;
        case SUBTYPE:
            newType = symbol->subtype;
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
    for (const auto group : mf->groups) {
        resolveGroupTypes(group, *mf);
    }
    for (const auto subtype : mf->subtypes) {
        subtype->subtype = resolveType(subtype->subtype, mf);
    }
    for (const auto [_, func] : mf->funcs) {
        if (dynamic_cast<LgsMainFunc*>(func)) continue;
        resolveFuncTypes(func->funcType, *mf);
    }
}

void LgsTypeResolver::resolveObjTypes(LgsObject* obj, LgsFile& file) {
    for (const auto& enum_ : obj->enums) {
        file.symbolTable.addSymbol(LgsSymbol(enum_), &errHandler);
        for (const auto field : enum_->fields) {
            file.symbolTable.addSymbol(LgsSymbol(field), &errHandler);
        }
    }
    for (const auto& field : obj->fields) {
        if (obj->name == field->type->getName()) {
            field->type = obj;
        } else {
            field->type = resolveType(field->type, &file);
        }
    }
    for (const auto& [_, method] : obj->methods) {
        if (obj->name == method->type->getName()) {
            method->funcType->rt = obj;
        } else {
            method->funcType->rt = resolveType(method->funcType->rt, &file);
        }
        for (auto& param : method->funcType->params) {
            if (obj->name == param.type->getName()) {
                param.type = obj;
            } else {
                param.type = resolveType(param.type, &file);
            }
        }
    }
    for (auto& interface : obj->interfaces) {
        interface = resolveType(interface, &file);
    }
    for (const auto& ioPair : obj->ioPairs) {
        resolveIOPair(ioPair, obj);
    }
}

void LgsTypeResolver::resolveInterfaceTypes(LgsInterface* interface, LgsFile& file) {
    for (const auto& field : interface->fields) {
        field->type = resolveType(field->type, &file);
    }
    for (const auto& [_, method] : interface->methods) {
        resolveFuncTypes(method->funcType, file);
    }
    for (auto& i : interface->interfaces) {
        i = resolveType(i, &file);
    }
}

void LgsTypeResolver::resolveIterable(LgsIterable* iterable, LgsFile& file) {
    iterable->baseType = resolveType(iterable->baseType, &file);
}

void LgsTypeResolver::resolveFuncTypes(LgsFuncType* funcType, LgsFile& file) {
    for (auto & param : funcType->params) {
        param.type = resolveType(param.type, &file);
    }
    funcType->rt = !funcType->rt ? &LGS_VOID : resolveType(funcType->rt, &file);
}

void LgsTypeResolver::resolveGroupTypes(LgsGroup* group, LgsFile& file) {
    for (auto& type : group->types) {
        type = resolveType(type, &file);
    }
}

void LgsTypeResolver::resolveIOPair(LgsIOPair* ioPair, LgsObject* obj) const {
    ioPair->openFunc = obj->getMethod(ioPair->openFuncName);
    ioPair->openFunc->funcType->isInIOPair = true;
    if (!ioPair->openFunc) {
        errHandler.addError(E10005, &ioPair->openFunc->location, {ioPair->openFuncName, obj->pname()});
    }
    ioPair->closeFunc = obj->getMethod(ioPair->closeFuncName);
    ioPair->closeFunc->funcType->isInIOPair = true;
    if (!ioPair->closeFunc) {
        errHandler.addError(E10005, &ioPair->closeFunc->location, {ioPair->closeFuncName, obj->pname()});
    }
}

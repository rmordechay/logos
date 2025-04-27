#include "analysis/LgsAnalyser.h"

#include "CodeGenMetadata.h"
#include "LgsFile.h"
#include "LgsGlobals.h"
#include "LgsInterfaceFile.h"
#include "LgsMainFile.h"
#include "LgsObjectFile.h"
#include "funcs/LgsMethodImpl.h"

LgsType* LgsAnalyser::resolveType(LgsType* type) {
    if (!dynamic_cast<LgsUnknownType*>(type)) return type;
    auto typeName = type->getName();
    const auto nullable = type->nullable;
    if (globals.symbols.find(typeName) == globals.symbols.end()) {
        handleError(E10006, &type->location, {typeName});
        return nullptr;
    }
    const auto symbol = &globals.symbols[typeName];
    delete type;
    LgsType* newType = nullptr;
    if (symbol->type == OBJECT) {
        symbol->object->nullable = nullable;
        newType = symbol->object;
    }
    if (symbol->type == INTERFACE) {
        symbol->interface->nullable = nullable;
        newType = symbol->interface;
    }
    if (symbol->type == ENUM) {
        symbol->lgsEnum->nullable = nullable;
        newType = symbol->lgsEnum;
    }
    if (symbol->type == ENUM_FIELD) {
        symbol->enumField->parent->nullable = nullable;
        newType = symbol->enumField->parent;
    }
    assert(newType);
    return newType;
}

void LgsAnalyser::resolveGlobalTypes(const vector<LgsFile*>& files) {
    for (const auto& file : files) {
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto& object : mainFile->objects) {
                resolveObjMemberTypes(object);
            }
            for (const auto& func : mainFile->funcs) {
                resolveFuncTypes(&func->signature);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            resolveObjMemberTypes(objFile->obj);
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            for (const auto& signature : interfaceFile->interface->funcSignatures) {
                resolveFuncTypes(signature);
            }
        }
    }
}

void LgsAnalyser::resolveObjMemberTypes(LgsObject* const& obj) {
    for (const auto& [_, field] : obj->fields) {
        field->type = resolveType(field->type);
        field->parent = obj;
    }
    for (const auto& [_, method] : obj->methods) {
        for (const auto& overload : method) {
            resolveFuncTypes(&overload->signature);
        }
    }
    for (int i = 0; i < obj->implements.size(); ++i) {
        obj->implements[i] = resolveType(obj->implements[i]);
    }
}

void LgsAnalyser::resolveFuncTypes(LgsFuncSignature* signature) {
    signature->type = resolveType(signature->type);
    for (int i = 0; i < signature->params.size(); ++i) {
        const auto lgsParam = signature->params[i];
        if (lgsParam.func) {
            resolveFuncTypes(&lgsParam.func->signature);
        }
        signature->params[i].type = resolveType(signature->params[i].type);
    }
}

string LgsAnalyser::formatMsg(const string& errMsg, const vector<string>& args) const {
    auto pos = 0;
    auto argIndex = 0;
    auto result = errMsg;
    while ((pos = result.find(ERROR_PLACEHOLDER, pos)) != string::npos && argIndex < args.size()) {
        result.replace(pos, ERROR_PLACEHOLDER.size(), args[argIndex]);
        pos += args[argIndex].length();
        argIndex++;
    }
    return result;
}

void LgsAnalyser::handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args) {
    setUnsuccessful();
    const auto errMsg = formatMsg(lgsErr.msg, args);
    errors.emplace_back(LgsError{.msg = errMsg, .errCode = lgsErr.errCode});
    cout <<  "Error: "  << errMsg << endl;
    if (location) {
        assert(location->lineNumber != 0);
        assert(filePath != "");
        const auto lineNumber = to_string(location->lineNumber);
        const auto pos = to_string(location->posInLine);
        const auto fullPath = filePath.string() + ":" + lineNumber + ":" + pos;
        const auto path = "\tat " + fullPath;
        cout << path << endl;
    }
}

void LgsAnalyser::setUnsuccessful() {
    successful = false;
}
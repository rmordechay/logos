#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <cmath>
#include <sstream>

#include "LgsConfigs.h"

static std::string formatElement(const Lgs_TypeInfo* type, void* value) {
    if (!value) return LGS_NULL_LITERAL;
    std::ostringstream str;
    switch (type->kind) {
    case RTT_ANY: str << value; break;
    case RTT_BOOL: str << (*static_cast<bool*>(value) ? "true" : "false"); break;
    case RTT_BYTE: str << *static_cast<int8_t*>(value); break;
    case RTT_SHORT: str << *static_cast<int16_t*>(value); break;
    case RTT_INT: str << *static_cast<int32_t*>(value); break;
    case RTT_LONG: str << *static_cast<int64_t*>(value); break;
    case RTT_SIZE: str << *static_cast<size_t*>(value); break;
    case RTT_UBYTE: str << *static_cast<uint8_t*>(value); break;
    case RTT_USHORT: str << *static_cast<uint16_t*>(value); break;
    case RTT_UINT: str << *static_cast<uint32_t*>(value); break;
    case RTT_ULONG: str << *static_cast<uint64_t*>(value); break;
    case RTT_FLOAT: str << *static_cast<float_t*>(value); break;
    case RTT_DOUBLE: str << *static_cast<double_t*>(value); break;
    case RTT_ENUM:
    case RTT_STR: {
        const auto lgsStr = static_cast<Lgs_StrExpr*>(value);
        assert(lgsStr->level <= LGS_MAX_LEVEL);
        if (!lgsStr->data) return LGS_NULL_LITERAL;
        if (std::strcmp(lgsStr->data, "") == 0) return "\"\"";
        str << static_cast<Lgs_StrExpr*>(value)->data;
        break;
    }
    case RTT_CHAR: str << "'" << *static_cast<const char*>(value) << "'"; break;
    case RTT_OBJECT: {
        const auto obj = type->object;
        str << obj->name << "{";
        for (int i = 0; i < obj->fieldsCount; ++i) {
            const auto fieldName = obj->fields[i].name;
            const auto fieldOffset = obj->fields[i].offset;
            const auto fieldType = obj->fields[i].type;
            void* fieldPtr = static_cast<char*>(value) + fieldOffset;
            if (fieldType->isHeap) {
                fieldPtr = *static_cast<void**>(fieldPtr);
            }
            str << fieldName << '=';
            str << formatElement(fieldType, fieldPtr);
            if (i < obj->fieldsCount - 1) str << ", ";
        }
        str << "}";
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        const auto dArr = static_cast<Lgs_DArrExpr*>(value);
        if (!dArr->data && dArr->capacity == 0) return LGS_NULL_LITERAL;
        str << "[";
        for (int i = 0; i < dArr->length; ++i) {
            void* element = dArr->data + dArr->baseType->size * i;
            if (dArr->baseType->isHeap) {
                element = *static_cast<void**>(element);
            }
            str << formatElement(dArr->baseType, element);
            if (i < dArr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_SARRAY: {
        const auto sArr = type->sArr;
        if (sArr->baseType->kind == RTT_CHAR) {
            str << static_cast<char*>(value);
            break;
        }
        str << "[";
        auto offset = 0;
        for (int i = 0; i < sArr->length; ++i) {
            void* element = static_cast<char*>(value) + offset;
            if (sArr->baseType->isHeap) {
                element = *static_cast<void**>(element);
            }
            str << formatElement(sArr->baseType, element);
            if (i < sArr->length - 1) str << ", ";
            offset += sArr->baseType->isHeap ? sizeof(void*) : sArr->baseType->size;
        }
        str << "]";
        break;
    }
    case RTT_VEC: {
        const auto vec = type->vec;
        str << "Vec" << std::to_string(vec->length) << "(";
        auto offset = 0;
        for (int i = 0; i < vec->length; ++i) {
            void* element = static_cast<char*>(value) + offset;
            str << formatElement(vec->baseType, element);
            if (i < vec->length - 1) str << ", ";
            offset += vec->baseType->size;
        }
        str << ")";
        break;
    }
    case RTT_NULLABLE: {
        const auto baseType = type->baseType;
        if (!baseType) return LGS_NULL_LITERAL;
        const auto isSetPtr = static_cast<char*>(value) + baseType->size;
        const auto isSet = *reinterpret_cast<bool*>(isSetPtr);
        if (isSet) str << formatElement(baseType, value);
        else str << LGS_NULL_LITERAL;
        break;
    }
    case RTT_MAP: {
        const auto hashMap = static_cast<Lgs_HashMap*>(value);
        const auto map = hashMap->type->map;
        str << '{';
        auto isFirst = true;
        for (int i = 0; i < hashMap->capacity; ++i) {
            const auto entry = hashMap->entries[i];
            if (!entry) continue;
            if (!isFirst) str << ", ";
            isFirst = false;
            str << formatElement(map->key, entry->key);
            str << ": ";
            str << formatElement(map->value, entry->value);
        }
        str << '}';
        break;
    }
    case RTT_MATRIX:
    default:
        assert(0);
    }
    return str.str();
}

extern "C" void Lgs_print(const Lgs_TypeInfo* type, void* v) {
    printf("%s\n", formatElement(type, v).c_str());
}

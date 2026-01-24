#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <sstream>

#include "LgsConfigs.h"

static std::string formatElement(const Lgs_TypeKind kind, void* type, void* value) {
    if (!value) return LGS_NULL_LITERAL;
    std::ostringstream str;
    switch (kind) {
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
    case RTT_FLOAT: str << *static_cast<float*>(value); break;
    case RTT_DOUBLE: str << *static_cast<double*>(value); break;
    case RTT_ENUM:
    case RTT_STR: {
        const auto lgsStr = static_cast<Lgs_Str*>(value);
        assert(lgsStr->level <= LGS_MAX_LEVEL);
        if (!lgsStr->data) return LGS_NULL_LITERAL;
        str << "\"" << static_cast<Lgs_Str*>(value)->data << "\"";
    }
    break;
    case RTT_CHAR: str << "'" << *static_cast<const char*>(value) << "'"; break;
    case RTT_OBJECT: {
        const auto objPtr = static_cast<char*>(value) + sizeof(size_t);
        const auto obj = *reinterpret_cast<Lgs_Object**>(objPtr);
        str << "{";
        for (int i = 0; i < obj->fieldsCount; ++i) {
            const auto fieldName = obj->fields[i].name;
            const auto fieldOffset = obj->fields[i].offset;
            const auto fieldKind = obj->fields[i].kind;
            const auto fieldType = obj->fields[i].type;
            void* fieldPtr = static_cast<char*>(value) + fieldOffset;
            if (fieldKind == RTT_OBJECT || fieldKind == RTT_DARRAY || fieldKind == RTT_STR) {
                fieldPtr = *static_cast<void**>(fieldPtr);
            }
            str << fieldName << '=';
            str << formatElement(fieldKind, fieldType, fieldPtr);
            if (i < obj->fieldsCount - 1) str << ", ";
        }
        str << "}";
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        const auto dArr = static_cast<Lgs_DArrayExpr*>(value);
        const auto baseKind = dArr->baseType->kind;
        str << "[";
        for (int i = 0; i < dArr->length; ++i) {
            void* element = dArr->data + dArr->baseType->size * i;
            if (baseKind == RTT_OBJECT || baseKind == RTT_DARRAY || baseKind == RTT_STR) {
                element = *static_cast<void**>(element);
            }
            str << formatElement(baseKind, dArr->baseType, element);
            if (i < dArr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_SARRAY: {
        const auto sArr = static_cast<Lgs_SArr*>(type);
        const auto baseKind = sArr->baseType->kind;
        str << "[";
        for (int i = 0; i < sArr->length; ++i) {
            void* element = static_cast<char*>(value) + sArr->baseType->size * i;
            if (baseKind == RTT_OBJECT || baseKind == RTT_DARRAY || baseKind == RTT_STR) {
                element = *static_cast<void**>(element);
            }
            str << formatElement(baseKind, nullptr, element);
            if (i < sArr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_NULLABLE: {
        const auto nullable = static_cast<Lgs_Nullable*>(type);
        if (nullable->isPtr) {
            str << formatElement(nullable->baseType->kind, nullable->baseType, *static_cast<void**>(value));
        } else {
            const auto isSetPtr = static_cast<char*>(value) + nullable->baseType->size;
            const auto isSet = *reinterpret_cast<bool*>(isSetPtr);
            if (isSet) str << formatElement(nullable->baseType->kind, nullable->baseType, value);
            else str << LGS_NULL_LITERAL;
        }
        break;
    }
    case RTT_VEC2:
    case RTT_VEC3:
    case RTT_VEC4:
    case RTT_MATRIX:
    case RTT_MAP:
    case RTT_COMPLEX:
    default:
        assert(0);
    }
    return str.str();
}

extern "C" void Lgs_print(const Lgs_TypeKind kind, void* type, void* v) {
    printf("%s\n", formatElement(kind, type, v).c_str());
}

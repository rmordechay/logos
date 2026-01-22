#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <sstream>

static std::string formatElement(const Lgs_TypeKind kind, void* value) {
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
        if (!lgsStr->data) return LGS_NULL_LITERAL;
        str << "\"" << static_cast<Lgs_Str*>(value)->data << "\"";
    }
    break;
    case RTT_CHAR: str << "'" << *static_cast<const char*>(value) << "'"; break;
    case RTT_OBJECT: {
        const auto level = static_cast<size_t*>(value);
        const auto obj = *reinterpret_cast<Lgs_Object**>(level + 1);
        str << "{";
        for (int i = 0; i < obj->fieldsCount; ++i) {
            const auto fieldName = obj->fieldNames[i];
            const auto fieldOffset = obj->fieldOffsets[i];
            const auto fieldKind = obj->fieldKinds[i];
            void* fieldPtr = static_cast<char*>(value) + fieldOffset;
            if (fieldKind == RTT_OBJECT || fieldKind == RTT_DARRAY) {
                fieldPtr = *static_cast<void**>(fieldPtr);
            }
            str << fieldName << '=';
            str << formatElement(fieldKind, fieldPtr);
            if (i < obj->fieldsCount - 1) str << ", ";
        }
        str << "}";
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        const auto arr = static_cast<Lgs_DArrayExpr*>(value);
        str << "[";
        for (int i = 0; i < arr->length; ++i) {
            const auto element = arr->data + arr->baseType->size * i;
            str << formatElement(arr->baseType->kind, element);
            if (i < arr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_SARRAY: {
        str << "[";
        str << "]";
        break;
    }
    case RTT_VEC2:
    case RTT_VEC3:
    case RTT_VEC4:
    case RTT_MATRIX:
    case RTT_NULLABLE:
    case RTT_MAP:
    case RTT_COMPLEX:
    default: assert(0);
    }
    return str.str();
}

extern "C" void Lgs_print(const Lgs_TypeKind kind, void* v) {
    printf("%s\n", formatElement(kind, v).c_str());
}

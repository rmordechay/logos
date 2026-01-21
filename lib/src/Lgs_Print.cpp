#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <sstream>

#include "LgsConfigs.h"

static std::string formatElement(const Lgs_TypeKind kind, void* rtt, void* value) {
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
    case RTT_STR: str << "\"" << static_cast<Lgs_Str*>(value)->data << "\""; break;
    case RTT_CHAR: str << "'" << *static_cast<const char*>(value) << "'"; break;
    case RTT_OBJECT: {
        const auto obj = static_cast<Lgs_Object*>(rtt);
        auto offset = LEVEL_SIZE;
        str << "{";
        for (int i = 0; i < obj->fieldsCount; ++i) {
            const auto fieldName = obj->fieldNames[i];
            const auto fieldType = obj->fieldTypes[i];
            const void* fieldPtr = static_cast<char*>(value) + offset;
            str << fieldName << '=';
            str << fieldPtr;
            if (i < obj->fieldsCount - 1) str << ", ";
            if (!fieldType) continue;
            offset += fieldType->size;
        }
        str << "}";
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        str << "[";
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

extern "C" void Lgs_print(const Lgs_TypeKind kind, void* rtt, void* v) {
    printf("%s\n", formatElement(kind, rtt, v).c_str());
}

#include "Lgs_DArrayExpr.h"
#include "Lgs_Types.h"
#include "LgsDefinitions.h"
#include <cassert>
#include <sstream>

std::string formatArray(const Lgs_DArrayExpr* arr);
std::string formatElement(Lgs_TypeKind type, void* elem);

extern "C" void Lgs_print(const Lgs_TypeKind rtt, void* v) {
    printf("%s\n", formatElement(rtt, v).c_str());
}

std::string formatElement(const Lgs_TypeKind type, void* elem) {
    if (!elem) return LGS_NULL_LITERAL;
    std::ostringstream str;
    switch (type) {
    case RTT_ANY: {
        str << elem;
        break;
    }
    case RTT_BOOL: {
        str << (*static_cast<bool*>(elem) ? "true" : "false");
        break;
    }
    case RTT_BYTE: {
        str << *static_cast<int8_t*>(elem);
        break;
    }
    case RTT_SHORT: {
        str << *static_cast<int16_t*>(elem);
        break;
    }
    case RTT_INT: {
        str << *static_cast<int32_t*>(elem);
        break;
    }
    case RTT_LONG: {
        str << *static_cast<int64_t*>(elem);
        break;
    }
    case RTT_SIZE: {
        str << *static_cast<size_t*>(elem);
        break;
    }
    case RTT_UBYTE: {
        str << *static_cast<uint8_t*>(elem);
        break;
    }
    case RTT_USHORT: {
        str << *static_cast<uint16_t*>(elem);
        break;
    }
    case RTT_UINT: {
        str << *static_cast<uint32_t*>(elem);
        break;
    }
    case RTT_ULONG: {
        str << *static_cast<uint64_t*>(elem);
        break;
    }
    case RTT_FLOAT: {
        str << *static_cast<float*>(elem);
        break;
    }
    case RTT_DOUBLE: {
        str << *static_cast<double*>(elem);
        break;
    }
    case RTT_TYPE:
    case RTT_ENUM:
    case RTT_STR: {
        str << static_cast<const char*>(elem);
        break;
    }
    case RTT_CHAR: {
        str << *static_cast<const char*>(elem);
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        const auto nested = static_cast<Lgs_DArrayExpr*>(elem);
        str << formatArray(nested);
        break;
    }
    case RTT_VEC2:
    case RTT_VEC3:
    case RTT_VEC4:
    case RTT_MATRIX:
    case RTT_SARRAY:
    case RTT_MAP:
    case RTT_NULLABLE:
    case RTT_OBJECT: {
        assert(0);
    }
    case RTT_VOID:
    case RTT_UNKNOWN: {
        assert(0);
    }
    }
    return str.str();
}

std::string formatArray(const Lgs_DArrayExpr* arr) {
    std::ostringstream oss;
    oss << "[";
    const size_t len = Lgs_DArrayExpr_len(arr);
    for (size_t i = 0; i < len; ++i) {
        void* elem = Lgs_DArrayExpr_get(arr, i);
        oss << formatElement(arr->baseType, elem);
        if (i < len - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}

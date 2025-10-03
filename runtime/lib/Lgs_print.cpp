#include "Lgs_darray.h"
#include "Lgs_types.h"
#include "types/primitives/LgsBool.h"
#include "utils/LgsUtils.h"

std::string formatArray(const Lgs_darray* arr);

std::string formatElement(const Lgs_RTType type, const void* elem) {
    std::ostringstream oss;
    switch (type) {
    case RTT_CHAR:
        oss << *static_cast<const char*>(elem);
        break;
    case RTT_BOOL:
        oss << (*static_cast<const uint8_t*>(elem) ? LgsBool::trueLiteral : LgsBool::falseLiteral);
        break;
    case RTT_BYTE:
        oss << *static_cast<const int8_t*>(elem);
        break;
    case RTT_SHORT:
        oss << *static_cast<const int16_t*>(elem);
        break;
    case RTT_INT:
        oss << *static_cast<const int32_t*>(elem);
        break;
    case RTT_LONG:
        oss << *static_cast<const int64_t*>(elem);
        break;
    case RTT_SIZE:
        oss << *static_cast<const size_t*>(elem);
        break;
    case RTT_UBYTE:
        oss << static_cast<unsigned>(*static_cast<const uint8_t*>(elem));
        break;
    case RTT_USHORT:
        oss << *static_cast<const uint16_t*>(elem);
        break;
    case RTT_UINT:
        oss << *static_cast<const uint32_t*>(elem);
        break;
    case RTT_ULONG:
        oss << *static_cast<const uint64_t*>(elem);
        break;
    case RTT_FLOAT:
        oss << *static_cast<const float*>(elem);
        break;
    case RTT_DOUBLE:
        oss << *static_cast<const double*>(elem);
        break;
    case RTT_STR: {
        oss << *static_cast<const char* const*>(elem);
        break;
    }
    case RTT_VEC2: {
        const auto vec = *static_cast<const Lgs_vec2* const*>(elem);
        oss << '<' << vec->x << ", " << vec->y << '>';
        break;
    }
    case RTT_VEC3: {
        const auto vec = *static_cast<const Lgs_vec3* const*>(elem);
        oss << '<' << vec->x << ", " << vec->y << ", " << vec->z << '>';
        break;
    }
    case RTT_VEC4: {
        const auto vec = *static_cast<const Lgs_vec4* const*>(elem);
        oss << '<' << vec->x << ", " << vec->y << ", " << vec->z << ", " << vec->w << '>';
        break;
    }
    case RTT_DARRAY: {
        const auto nested = *static_cast<const Lgs_darray* const*>(elem);
        oss << formatArray(nested);
        break;
    }
    case RTT_ANY:
        oss << elem;
        break;
    case RTT_VOID:
    case RTT_SARRAY:
    case RTT_SET:
    case RTT_MAP:
    case RTT_OBJECT:
    case RTT_TYPE:
    case RTT_UNKNOWN:
        assert(0);
    }
    return oss.str();
}

std::string formatArray(const Lgs_darray* arr) {
    std::ostringstream oss;
    oss << "[";
    const size_t len = Lgs_DArray_len(arr);
    for (size_t i = 0; i < len; ++i) {
        const void* elem = Lgs_DArray_get(arr, i);
        oss << formatElement(arr->baseType, elem);
        if (i < len - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}

extern "C" void Lgs_print(const char* fmt, const Lgs_RTType rtt, const void* v) {
    if (!v) assert(0);
    printf(fmt, formatElement(rtt, v).c_str());
    printf("\n");
}

extern "C" void Lgs_printError(const char* fmt) {
    formatAndLogError(fmt);
}

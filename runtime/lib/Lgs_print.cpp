#include "Lgs_DArray.h"
#include "Lgs_types.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsNull.h"
#include "types/primitives/LgsBool.h"
#include <sstream>

std::string formatArray(Lgs_DArray* arr);
std::string formatElement(Lgs_rttype type, void* elem);

extern "C" void Lgs_print(const Lgs_rttype rtt, void* v) {
    if (v) printf("%s\n", formatElement(rtt, v).c_str());
    else printf("%s\n", LGS_NULL_LITERAL);
}

std::string formatElement(const Lgs_rttype type, void* elem) {
    std::ostringstream oss;
    switch (type) {
    case RTT_TYPE:
    case RTT_STR:
        oss << static_cast<const char*>(elem);
        break;
    case RTT_CHAR:
        oss << *static_cast<const char*>(elem);
        break;
    case RTT_BOOL:
        oss << (*static_cast<bool*>(elem) ? LgsBool::trueLiteral : LgsBool::falseLiteral);
        break;
    case RTT_BYTE:
        oss << *static_cast<int8_t*>(elem);
        break;
    case RTT_SHORT:
        oss << *static_cast<int16_t*>(elem);
        break;
    case RTT_INT:
        oss << *static_cast<int32_t*>(elem);
        break;
    case RTT_LONG:
        oss << *static_cast<int64_t*>(elem);
        break;
    case RTT_SIZE:
        oss << *static_cast<size_t*>(elem);
        break;
    case RTT_UBYTE:
        oss << *static_cast<uint8_t*>(elem);
        break;
    case RTT_USHORT:
        oss << *static_cast<uint16_t*>(elem);
        break;
    case RTT_UINT:
        oss << *static_cast<uint32_t*>(elem);
        break;
    case RTT_ULONG:
        oss << *static_cast<uint64_t*>(elem);
        break;
    case RTT_FLOAT:
        oss << *static_cast<const float_t*>(elem);
        break;
    case RTT_DOUBLE:
        oss << *static_cast<const double_t*>(elem);
        break;
    case RTT_VEC2: {
        const auto vec = static_cast<const Lgs_vec2*>(elem);
        oss << '<' << vec->x << ", " << vec->y << '>';
        break;
    }
    case RTT_VEC3: {
        const auto vec = static_cast<const Lgs_vec3*>(elem);
        oss << '<' << vec->x << ", " << vec->y << ", " << vec->z << '>';
        break;
    }
    case RTT_VEC4: {
        const auto vec = static_cast<const Lgs_vec4*>(elem);
        oss << '<' << vec->x << ", " << vec->y << ", " << vec->z << ", " << vec->w << '>';
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        const auto nested = static_cast<Lgs_DArray*>(elem);
        oss << formatArray(nested);
        break;
    }
    case RTT_NULLABLE: {
        const auto nullable = static_cast<Lgs_nullableInt*>(elem);
        if (nullable->isSet) {
            oss << nullable->v;
        } else {
            oss << LGS_NULL_LITERAL;
        }
        break;
    }
    case RTT_ANY:
        oss << elem;
        break;
    case RTT_SARRAY:
    case RTT_MAP:
    case RTT_OBJECT:
    case RTT_VOID:
    case RTT_UNKNOWN:
        assert(0);
    }
    return oss.str();
}

std::string formatArray(Lgs_DArray* arr) {
    std::ostringstream oss;
    oss << "[";
    const size_t len = Lgs_DArray_len(arr);
    for (size_t i = 0; i < len; ++i) {
        void* elem = Lgs_DArray_get(arr, i);
        oss << formatElement(arr->baseType, elem);
        if (i < len - 1) {
            oss << ", ";
        }
    }
    oss << "]";
    return oss.str();
}
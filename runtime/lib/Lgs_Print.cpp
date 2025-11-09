#include "Lgs_DArray.h"
#include "Lgs_Types.h"
#include "LgsDefinitions.h"
#include <cassert>
#include <sstream>
#include <cmath>

std::string formatArray(const Lgs_DArray* arr);
std::string formatElement(Lgs_RTType type, void* elem);

extern "C" void Lgs_print(const Lgs_RTType rtt, void* v) {
    printf("%s\n", formatElement(rtt, v).c_str());
}

std::string formatElement(const Lgs_RTType type, void* elem) {
    std::ostringstream oss;
    switch (type) {
    case RTT_BOOL:
        oss << (reinterpret_cast<intptr_t>(elem) ? "true" : "false");
        return oss.str();
    case RTT_BYTE:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_SHORT:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_INT:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_LONG:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_SIZE:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_UBYTE:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_USHORT:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_UINT:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_ULONG:
        oss << reinterpret_cast<intptr_t>(elem);
        return oss.str();
    case RTT_FLOAT:
        oss << reinterpret_cast<float&>(elem);
        return oss.str();
    case RTT_DOUBLE:
        oss << reinterpret_cast<double&>(elem);
        return oss.str();
    default:
        break;
    }
    if (!elem) printf("%s\n", LGS_NULL_LITERAL);
    switch (type) {
    case RTT_TYPE:
    case RTT_ENUM:
    case RTT_STR:
        oss << static_cast<const char*>(elem);
        break;
    case RTT_CHAR:
        oss << *static_cast<const char*>(elem);
        break;
    case RTT_VEC2: {
        const auto vec = static_cast<const Lgs_Vec2*>(elem);
        oss << '<' << vec->x << ", " << vec->y << '>';
        break;
    }
    case RTT_VEC3: {
        const auto vec = static_cast<const Lgs_Vec3*>(elem);
        oss << '<' << vec->x << ", " << vec->y << ", " << vec->z << '>';
        break;
    }
    case RTT_VEC4: {
        const auto vec = static_cast<const Lgs_Vec4*>(elem);
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
        const auto nullable = static_cast<Lgs_NullableInt*>(elem);
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
    default:
        assert(0);
    }
    return oss.str();
}

std::string formatArray(const Lgs_DArray* arr) {
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

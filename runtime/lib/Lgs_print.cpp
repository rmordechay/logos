#include "Lgs_types.h"
#include "types/primitives/LgsBool.h"

extern "C" void Lgs_print(const char* fmt, const Lgs_RTType rtt, const void* v) {
    switch (rtt) {
    case RTT_CHAR: {
        const char ch = *static_cast<const char*>(v);
        printf(fmt, ch);
        break;
    }
    case RTT_BOOL: {
        const char b = *static_cast<const uint8_t*>(v);
        if (b) printf(fmt, LgsBool::trueLiteral);
        else printf(fmt, LgsBool::falseLiteral);
        break;
    }
    case RTT_BYTE: {
        const auto b = *static_cast<const int8_t*>(v);
        printf(fmt, b);
        break;
    }
    case RTT_SHORT: {
        const auto s = *static_cast<const int16_t*>(v);
        printf(fmt, s);
        break;
    }
    case RTT_INT: {
        const auto str = *static_cast<const int32_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_LONG: {
        const auto str = *static_cast<const int64_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_SIZE: {
        const auto str = *static_cast<const size_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_FLOAT: {
        const auto str = *static_cast<const float_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_DOUBLE: {
        const auto str = *static_cast<const double_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_STR: {
        const auto str = static_cast<const char*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_VEC2: {
        const auto vec = static_cast<const Lgs_vec2*>(v);
        printf(fmt, vec->x, vec->y);
        break;
    }
    case RTT_VEC3: {
        const auto vec = static_cast<const Lgs_vec3*>(v);
        printf(fmt, vec->x, vec->y, vec->z);
        break;
    }
    case RTT_VEC4: {
        const auto vec = static_cast<const Lgs_vec4*>(v);
        printf(fmt, vec->x, vec->y, vec->z, vec->w);
        break;
    }
    case RTT_SARRAY:
    case RTT_DARRAY:
    case RTT_OBJECT:
    case RTT_TYPE:
    case RTT_VOID:
    case RTT_UNKNOWN:
        assert(0);
    }
    printf("\n");
}

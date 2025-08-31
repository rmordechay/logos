#include "Lgs_types.h"

extern "C" void Lgs_print(const char* fmt, const LgsRTType rtt, const void* v) {
    switch (rtt) {
    case RTT_BOOL: {
        const char ch = *static_cast<const uint8_t*>(v);
        printf(fmt, ch);
        break;
    }
    case RTT_CHAR: {
        const char ch = *static_cast<const char*>(v);
        printf(fmt, ch);
        break;
    }
    case RTT_INT: {
        const auto str = *static_cast<const uint32_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_FLOAT: {
        const auto str = *static_cast<const float_t*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_STR: {
        const auto str = static_cast<const char*>(v);
        printf(fmt, str);
        break;
    }
    case RTT_VEC2: {
        const auto vec = static_cast<const Vec2*>(v);
        printf(fmt, vec->x, vec->y);
        break;
    }
    case RTT_VEC3: {
        const auto vec = static_cast<const Vec3*>(v);
        printf(fmt, vec->x, vec->y, vec->z);
        break;
    }
    case RTT_VEC4: {
        const auto vec = static_cast<const Vec4*>(v);
        printf(fmt, vec->x, vec->y, vec->z, vec->w);
        break;
    }
    case RTT_VOID:
        break;
    case RTT_UNKNOWN:
        return;
    }
    printf("\n");
}

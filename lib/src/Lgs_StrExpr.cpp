#include <cstring>

extern "C" size_t Lgs_Str_len(const char* str) {
    return std::strlen(str);
}

extern "C" size_t Lgs_Str_isEmpty(const char* str) {
    return std::strlen(str) == 0;
}

extern "C" size_t Lgs_Str_isNotEmpty(const char* str) {
    return std::strlen(str) != 0;
}

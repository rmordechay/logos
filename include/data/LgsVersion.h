#pragma once
#include <string>

struct LgsVersion {
    size_t major;
    size_t minor;
    size_t micro;
    std::string asStr() const;
    bool setVersion(const std::string& value);
};

inline std::string LgsVersion::asStr() const {
    return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(micro);
}

inline bool LgsVersion::setVersion(const std::string& value) {
    int consumed = 0;
    const auto s = std::sscanf(value.c_str(), "%lu.%lu.%lu%n", &major, &minor, &micro, &consumed) == 3;
    if (!s || value[consumed] != '\0') {
        return false;
    }
    return true;
}
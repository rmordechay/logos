#include "LgsDefinitions.h"
#include "Lgs_ArrayExpr.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <sstream>

static std::string formatElement(const Lgs_TypeInfo* rtt, void* value) {
    if (!value) return LGS_NULL_LITERAL;
    std::ostringstream str;
    switch (rtt->kind) {
    case RTT_OBJECT: {
        const auto fieldsCount = rtt->obj.fieldsCount;
        str << rtt->obj.name << "{";
        for (size_t i = 0; i < fieldsCount; ++i) {
            const auto fieldType = rtt->obj.fieldTypes[i];
            void* fieldPtr = static_cast<char*>(value) + rtt->obj.fieldOffsets[i];
            // if (fieldType->kind == RTT_OBJECT) {
            //     fieldPtr = *static_cast<void**>(fieldPtr);
            // }
            str << rtt->obj.fieldNames[i] << '=';
            str << formatElement(fieldType, fieldPtr);
            if (i < fieldsCount - 1) str << ", ";
        }
        str << "}";
        break;
    }
    case RTT_DARRAY: {
        std::println("{}", value);
        const auto dArrExpr = static_cast<Lgs_ArrayExpr*>(value);
        assert(dArrExpr->length <= LGS_DARRAY_MAX_LENGTH);
        const auto& [baseType] = rtt->dArray;
        str << "[";
        for (size_t i = 0; i < dArrExpr->length; ++i) {
            const auto element = dArrExpr->data + baseType->size * i;
            str << formatElement(baseType, element);
            if (i < dArrExpr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_SARRAY: {
        const auto sArr = rtt->sArray;
        const auto baseType = sArr.baseType;
        str << "[";
        for (size_t i = 0; i < sArr.len; ++i) {
            void* data = static_cast<char*>(value) + i * baseType->size;
            str << formatElement(baseType, data);
            if (i < sArr.len - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_MATRIX: {
        const auto& [rows, columns, baseType] = rtt->matrix;
        str << "Mat" << rows << "x" << columns << "[\n";
        for (size_t r = 0; r < rows; ++r) {
            str << "  [";
            for (size_t c = 0; c < columns; ++c) {
                const auto i = r * columns + c;
                void* data = static_cast<char*>(value) + i * baseType->size;
                str << formatElement(baseType, data);
                if (c + 1 < columns) str << ", ";
            }
            str << "]";
            if (r + 1 < rows) str << "\n";
        }
        str << "\n]";
        break;
    }
    case RTT_NULLABLE: {
        const auto& [baseType, isPtr] = rtt->nullable;
        if (isPtr) {
            value = *static_cast<void**>(value);
            str << formatElement(baseType, value);
        } else {
            const bool isSet = *(static_cast<bool*>(value) + baseType->size);
            if (isSet) str << formatElement(baseType, value);
            else str << LGS_NULL_LITERAL;
        }
        break;
    }
    case RTT_MAP: {
        const auto& [keyType, valueType] = rtt->map;
        const auto hashMap = static_cast<Lgs_HashMap*>(value);
        str << "{";
        auto isFirst = true;
        for (int i = 0; i < hashMap->capacity; ++i) {
            const auto entry = hashMap->entries[i];
            if (!entry) continue;
            if (!isFirst) str << ", ";
            isFirst = false;
            str << formatElement(keyType, entry) << ": ";
            str << formatElement(valueType, static_cast<char*>(entry) + keyType->size);
        }
        str << "}";
        break;
    }
    case RTT_COMPLEX: {
        const auto& [real, img] = rtt->complex;
        str << formatElement(real, value) << " + ";
        str << formatElement(img, static_cast<char*>(value) + real->size) << 'i';
        break;
    }
    default: assert(0);
    }
    return str.str();
}

extern "C" void Lgs_print(const Lgs_TypeInfo* rtt, void* v) {
    printf("%s\n", formatElement(rtt, v).c_str());
}

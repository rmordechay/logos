#include "LgsDefinitions.h"
#include "Lgs_Exprs.h"
#include "Lgs_Runtime.h"
#include "Lgs_Types.h"
#include <cassert>
#include <sstream>

#include "LgsConfigs.h"

static std::string formatElement(const Lgs_TypeInfo* rtt, void* value) {
    if (!value) return LGS_NULL_LITERAL;
    std::ostringstream str;
    switch (rtt->kind) {
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
    case RTT_CHAR: str << "\"" << *static_cast<const char*>(value) << "\""; break;
    case RTT_OBJECT: {
        const auto fieldsCount = rtt->obj.fieldsCount;
        str << rtt->obj.name << "{";
        auto offset = LEVEL_SIZE;
        for (size_t i = 0; i < fieldsCount; ++i) {
            const auto fieldType = rtt->obj.fieldTypes[i];
            void* fieldPtr = static_cast<char*>(value) + offset;
            if (fieldType->isHeap) {
                fieldPtr = *static_cast<void**>(fieldPtr);
            }
            str << rtt->obj.fieldNames[i] << '=';
            str << formatElement(fieldType, fieldPtr);
            if (i < fieldsCount - 1) str << ", ";
            offset += fieldType->size;
        }
        str << "}";
        break;
    }
    case RTT_SET:
    case RTT_DARRAY: {
        const auto dArrExpr = static_cast<Lgs_DArrayExpr*>(value);
        assert(dArrExpr->length <= LGS_DARRAY_MAX_LENGTH);
        const auto& [baseType] = rtt->dArray;
        str << "[";
        for (size_t i = 0; i < dArrExpr->length; ++i) {
            void* element = dArrExpr->data + baseType->size * i;
            if (baseType->isHeap) {
                element = *static_cast<void**>(element);
            }
            str << formatElement(baseType, element);
            if (i < dArrExpr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_SARRAY: {
        const auto sArr = rtt->sArray;
        const auto baseType = sArr.baseType;
        if (baseType->kind == RTT_CHAR) {
            str << "\"" << static_cast<char*>(value) << "\"";
            break;
        }
        str << "[";
        for (size_t i = 0; i < sArr.len; ++i) {
            void* data = static_cast<char*>(value) + i * baseType->size;
            str << formatElement(baseType, data);
            if (i < sArr.len - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_VEC2: {
        const auto& [baseType] = rtt->vec2;
        void* e1 = value;
        void* e2 = static_cast<char*>(e1) + baseType->size;
        str << "Vec2<";
        str << formatElement(baseType, e1) << ", ";
        str << formatElement(baseType, e2) << ">";
        break;
    }
    case RTT_VEC3: {
        const auto& [baseType] = rtt->vec3;
        void* e1 = value;
        void* e2 = static_cast<char*>(e1) + baseType->size;
        void* e3 = static_cast<char*>(e2) + baseType->size;
        str << "Vec3<";
        str << formatElement(baseType, e1) << ", ";
        str << formatElement(baseType, e2) << ", ";
        str << formatElement(baseType, e3) << ">";
        break;
    }
    case RTT_VEC4: {
        const auto& [baseType] = rtt->vec4;
        void* e1 = value;
        void* e2 = static_cast<char*>(e1) + baseType->size;
        void* e3 = static_cast<char*>(e2) + baseType->size;
        void* e4 = static_cast<char*>(e3) + baseType->size;
        str << "Vec4<";
        str << formatElement(baseType, e1) << ", ";
        str << formatElement(baseType, e2) << ", ";
        str << formatElement(baseType, e3) << ", ";
        str << formatElement(baseType, e4) << ">";
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

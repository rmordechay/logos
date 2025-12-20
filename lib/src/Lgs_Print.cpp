#include "LgsDefinitions.h"
#include "Lgs_DArrayExpr.h"
#include "Lgs_HashMap.h"
#include "Lgs_Types.h"
#include <cassert>
#include <sstream>

static std::string formatElement(const Lgs_TypeInfo* rtt, void* elem) {
    if (!elem) return LGS_NULL_LITERAL;
    std::ostringstream str;
    switch (rtt->kind) {
    case RTT_ANY: str << elem; break;
    case RTT_BOOL: str << (*static_cast<bool*>(elem) ? "true" : "false"); break;
    case RTT_BYTE: str << *static_cast<int8_t*>(elem); break;
    case RTT_SHORT: str << *static_cast<int16_t*>(elem); break;
    case RTT_INT: str << *static_cast<int32_t*>(elem); break;
    case RTT_LONG: str << *static_cast<int64_t*>(elem); break;
    case RTT_SIZE: str << *static_cast<size_t*>(elem); break;
    case RTT_UBYTE: str << *static_cast<uint8_t*>(elem); break;
    case RTT_USHORT: str << *static_cast<uint16_t*>(elem); break;
    case RTT_UINT: str << *static_cast<uint32_t*>(elem); break;
    case RTT_ULONG: str << *static_cast<uint64_t*>(elem); break;
    case RTT_FLOAT: str << *static_cast<float*>(elem); break;
    case RTT_DOUBLE: str << *static_cast<double*>(elem); break;
    case RTT_TYPE:
    case RTT_ENUM:
    case RTT_STR: {
        str << '"' << static_cast<char*>(elem) << '"';
        break;
    }
    case RTT_CHAR: str << '"' << *static_cast<const char*>(elem) << '"'; break;
    case RTT_SET:
    case RTT_DARRAY: {
        const auto dArrExpr = static_cast<Lgs_DArrayExpr*>(elem);
        assert(dArrExpr->length <= LGS_DARRAY_MAX_LENGTH);
        const auto& [baseType] = rtt->dArray;
        str << "[";
        for (size_t i = 0; i < dArrExpr->length; ++i) {
            auto data = Lgs_DArray_get(dArrExpr, rtt, i);
            str << formatElement(baseType, data);
            if (i < dArrExpr->length - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_SARRAY: {
        const auto& sArr = rtt->sArray;
        const auto baseType = sArr.baseType;
        size_t len = 0;
        void* base = nullptr;
        if (sArr.len == 0) {
            const auto sArrExpr = static_cast<Lgs_SArrayExpr*>(elem);
            base = sArrExpr->data;
            len = sArrExpr->length;
        } else {
            base = elem;
            len = sArr.len;
        }
        str << "[";
        for (size_t i = 0; i < len; ++i) {
            void* data = static_cast<char*>(base) + i * baseType->size;
            str << formatElement(baseType, data);
            if (i < len - 1) str << ", ";
        }
        str << "]";
        break;
    }
    case RTT_VEC2: {
        const auto& [baseType] = rtt->vec2;
        void* e1 = elem;
        void* e2 = static_cast<char*>(e1) + baseType->size;
        str << "Vec2<";
        str << formatElement(baseType, e1) << ", ";
        str << formatElement(baseType, e2) << ">";
        break;
    }
    case RTT_VEC3: {
        const auto& [baseType] = rtt->vec3;
        void* e1 = elem;
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
        void* e1 = elem;
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
                void* data = static_cast<char*>(elem) + i * baseType->size;
                str << formatElement(baseType, data);
                if (c + 1 < columns) str << ", ";
            }
            str << "]";
            if (r + 1 < rows) str << "\n";
        }
        str << "\n]";
        break;
    }
    case RTT_OBJECT: {
        const auto fieldsCount = rtt->obj.fieldsCount;
        str << "{";
        size_t offset = 0;
        for (size_t i = 0; i < fieldsCount; ++i) {
            const auto fieldType = rtt->obj.fieldTypes[i];
            const auto fieldName = rtt->obj.fieldNames[i];
            void* fieldValue = static_cast<char*>(elem) + offset;
            str << fieldName << '=';
            str << formatElement(fieldType, fieldValue);
            if (i < fieldsCount - 1) str << ", ";
            offset += fieldType->size;
        }
        str << "}";
        break;
    }
    case RTT_NULLABLE: {
        const auto& [baseType, isPtr] = rtt->nullable;
        if (isPtr) {
            str << formatElement(baseType, elem);
        } else {
            const bool isSet = *(static_cast<bool*>(elem) + baseType->size);
            if (isSet) str << formatElement(baseType, elem);
            else str << LGS_NULL_LITERAL;
        }
        break;
    }
    case RTT_MAP: {
        const auto& [keyType, valueType] = rtt->map;
        auto hashMap = static_cast<Lgs_HashMap*>(elem);
        str << "{";
        assert(0);
        str << "}";
        break;
    }
    case RTT_COMPLEX: {
        const auto& [real, img] = rtt->complex;
        str << formatElement(real, elem) << " + ";
        str << formatElement(img, static_cast<char*>(elem) + real->size) << 'i';
        break;
    }
    case RTT_VOID:
    case RTT_VARIADIC:
    case RTT_FUNC:
    case RTT_UNKNOWN:
    default: assert(0);
    }
    return str.str();
}

extern "C" void Lgs_print(const Lgs_TypeInfo* rtt, void* v) {
    printf("%s\n", formatElement(rtt, v).c_str());
}

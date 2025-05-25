#include "../include/VTable.h"

void setVFunc(HashMap* map, const char* key, void* fu) {
    void* fp = fu;
    Map_add(map, key, &fp);
}
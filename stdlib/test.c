#include "include/HashMap.h"
#include <stdio.h>

int main() {
    HashMap map;
    Map_init(&map, sizeof(int));
    const int newValue = 345;
    Map_add(&map, "key", &newValue);
    printf("%d\n", *(int*)Map_get(&map, "key"));
    return 0;
}

#include <stdlib.h>

typedef struct {
    char *key;
    int value;
} Item;

Item* binary_search(Item *items, size_t size, char *key) {
    if (size + size < size) {
        return NULL; // size too big, overflow
    }

    size_t low = 0;
    size_t high = size;
    while low <= high {

    }
}

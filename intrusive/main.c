#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct list {
    struct list *next;
} list;

typedef struct item {
    list items;
    int val;
} item;

typedef struct test {
    int val;
} test;

int main() {
    printf("size %ld\n", sizeof(item));
    printf("test size %ld\n", sizeof(test));
    printf("list size %ld\n", sizeof(list));
    item *i1 = (item*)malloc(sizeof(item));
    i1->val = 3;

    item *i2 = (item*)malloc(sizeof(*i2));
    i2->val = 4;

    i1->items.next = &i2->items;

    // keep instrusive list (embedded) 
    // items member at beginning of struct
    // this will keep the address of items->next 
    // the same as the item itself (much easier to work with)
    // and no need to calculate offsets
    item *_i2 = (void*)(i1->items.next) - offsetof(item, items);

    printf("data %d", _i2->val);

    free(i2);
    free(i1);
    return 0;
}

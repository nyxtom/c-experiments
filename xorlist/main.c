#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct List {
    struct node *head;
    struct node *tail;
} List;

typedef struct node {
    int item;
    struct node *np;
} node;

// previous ^ next = value (ptrdiff) (stored in node)
// previous ^ value = next (forward)
// value ^ next = previous (backward)
node *xor(node *a, node *b) {
    return (node*) ((uintptr_t) a ^ (uintptr_t) b);
}

void insert(List *self, int item, bool at_tail) {
    node *ptr = (node*) malloc(sizeof(node));
    ptr->item = item;

    if (NULL == self->head) {
        ptr->np = NULL;
        self->head = self->tail = ptr;
    } else if (at_tail) {
        ptr->np = xor(self->tail, NULL);
        self->tail->np = xor(ptr, xor(self->tail->np, NULL)); // ptrdiff = (ptrprev XOR ptrnext)
        self->tail = ptr;
    } else {
        ptr->np = xor(NULL, self->head);
        self->head->np = xor(ptr, xor(NULL, self->head->np));
        self->head = ptr;
    }
}

int delete(List *self, bool from_tail) {
    if (NULL == self->head) {
        printf("Empty list.\n");
        exit(1);
    } else if (from_tail) {
        node *ptr = self->tail;
        int item = ptr->item;
        node *prev = xor(ptr->np, NULL);

        // update head if prev is NULL, or set new next ptr
        if (NULL == prev) self->head = NULL;
        else prev->np = xor(ptr, xor(prev->np, NULL));

        // set new tail and free ptr
        self->tail = prev;
        free(ptr);
        ptr = NULL;

        return item;
    } else {
        node *ptr = self->head;
        int item = ptr->item;
        node *next = xor(NULL, ptr->np);

        // update tail if next is NULL, or set new prev ptr
        if (NULL == next) self->tail = NULL;
        else next->np = xor(ptr, xor(NULL, next->np));

        // set new head and free ptr
        self->head = next;
        free(ptr);
        ptr = NULL;

        return item;
    }
}

void list(List *self, bool reversed) {
    node *curr = self->head;
    if (reversed) curr = self->tail;
    node *prev = NULL, *next = NULL;

    while (NULL != curr) {
        printf("%d ", curr->item);
        if (reversed) {
            prev = xor(curr->np, next);
            next = curr;
            curr = prev;
        } else {
            next = xor(prev, curr->np);
            prev = curr;
            curr = next;
        }
    }

    printf("\n");
}

int main() {
    List *l = (List*) malloc(sizeof(List));
    for (int i = 1; i <= 10; i++) {
        insert(l, i, i < 6);
    }

    list(l, true);

    for (int i = 1; i <= 4; i++) {
        delete(l, i < 3);
    }

    list(l, true);
    free(l);
    l = NULL;
}

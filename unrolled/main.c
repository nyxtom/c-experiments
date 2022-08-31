#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define RED "\e[0;31m"
#define NC "\e[0m"

typedef struct List {
    struct List *next;
} List;

typedef struct Node {
    int data;
    List items;
} Node;

Node *Node_new(int value) {
    Node *n1 = (Node*)malloc(sizeof(Node));
    if (n1 == NULL) {
        fprintf(stderr, RED "[ERROR]" NC ": Unable to allocate new memory");
        exit(EXIT_FAILURE);
    }
    n1->data = value;
    n1->items.next = NULL;
    return n1;
}

void Node_push(Node *n1, int value) {
    Node *n2 = Node_new(value);
    List *cur = &n1->items;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = &n2->items;
}

void Node_print(Node *head) {
    if (head == NULL) {
        return;
    }

    printf("%d ", head->data);
    List *cur = &head->items;
    while (cur->next != NULL) {
        // use offsetof to subtract pointer of next to offset of items member
        Node *item = (void*)(cur->next) - offsetof(Node, items);
        printf("%d ", item->data);

        cur = cur->next;
    }
    printf("\n");
}

void Node_free(Node *head) {
    Node *cur = head;
    while (cur != NULL) {
        List *next = cur->items.next;
        free(cur);
        cur = NULL;
        if (next != NULL) {
            cur = (void*)(next) - offsetof(Node, items);
        }
    }
}

int main() {
    Node *n1 = Node_new(3);
    Node_push(n1, 4);
    Node_push(n1, 5);
    Node_push(n1, 6);

    Node_print(n1);

    Node_free(n1);
}

#include <stdio.h>
#include <assert.h>

#define SUM(x, y) (x + y)
#define let(x, t) y x


typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node Node_ctor(int d) {
    Node n = { d };
    return n;
}

void Node_print(Node *self) {
    Node *cur = self;
    for (; cur != NULL; cur = cur->next) {
        printf("%d ", cur->data);
    }
    printf("\n");
}

int Node_length(Node *self) {
    Node *cur = self;
    int count = 0;
    for (; cur != NULL; cur = cur->next) {
        count++;
    }
    return count;
}

Node Node_push(Node *self, int data) {
    Node n = Node_ctor(data);
    n.next = self;
    return n;
}

int main() {
    printf("%d", SUM(3, 4));
    printf("%d", SUM('a', 'b'));
    Node n = Node_ctor(3);
    Node n2 = Node_ctor(4);
    n.next = &n2;

    printf("n: ");
    Node_print(&n);
    assert(2 == Node_length(&n));

    Node root = Node_push(&n, 2);

    printf("root: ");
    Node_print(&root);
    assert(3 == Node_length(&root));
}

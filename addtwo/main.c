#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* s = (struct ListNode*)malloc(sizeof(struct ListNode));
    s->next = NULL;

    struct ListNode* cur = s;
    int carry = 0;
    while (l1 != NULL || l2 != NULL) {
        int val = carry;
        if (l1 != NULL) {
            val += l1->val;
        }
        if (l2 != NULL) {
            val += l2->val;
        }
        if (val > 9) {
            carry = 1;
            val = val % 10;
        } else {
            carry = 0;
        }
        cur->val = val;
        if (l1 != NULL) {
            l1 = l1->next;
        }
        if (l2 != NULL) {
            l2 = l2->next;
        }
        if (l1 != NULL || l2 != NULL || carry > 0) {
            cur->next = (struct ListNode*)malloc(sizeof(struct ListNode));
            cur = cur->next;
            cur->val = carry;
            cur->next = NULL;
        }
    }

    return s;
}

int main() {
    struct ListNode* l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->val = 2;
    l1->next->val = 4;
    l1->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->next->next->val = 3;

    struct ListNode* l2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->val = 5;
    l2->next->val = 6;
    l2->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->next->next->val = 4;
    struct ListNode* res = addTwoNumbers(l1, l2);

    while (res != NULL) {
        printf("%d", res->val);
        res = res->next;
    }

    printf("\n");
}

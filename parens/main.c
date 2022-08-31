#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool valid(char *s) {
    int len = strlen(s);
    int *stack = (int*)calloc(len, sizeof(int));
    int top = -1;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        bool match = top > -1;
        if (c == ')') {
            match = match && stack[top] == '(';
        } else if (c == '}') {
            match = match && stack[top] == '{';
        } else if (c == ']') {
            match = match && stack[top] == '[';
        } else if (c == '(' || c == '{' || c== '[') {
            stack[++top] = c;
            continue;
        } else {
            continue;
        }

        // decrement (pop from stack on match)
        if (match) { top--; }
        else { return false; }
    }

    free(stack);
    return top == -1;
}

int main() {
    assert(valid("(({[]}))"));
    assert(valid("({})"));
    assert(!valid("([]})"));
    assert(valid("(asd[])"));
}

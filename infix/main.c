#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// infix: single letter, operator, proceeded by one infix string and followed by another Infix string
// A
// A + B
// (A + B) + (C - D)

// prefix: single letter, operator, followed by two prefix strings, every prefix string longer than a single variable
// contains an operator, first operand and second operand
// A
// +AB
// ++AB-CD

// postfix: (reverse polish notation) single letter or operator, preceded by two postfix strings, every postfix string 
// longer than a single variable contains first and secondoperands followed by an operator
// AAB+
// AB+CD-+

// prefix and postfix = writing math iwhtout parens
// time to evaluate postfix/prefix is O(n), n = number elements in array

// create a stack
// for each char t in input
//      if t is operand
//          output t
//      else if right paren
//          pop and output tokens until left parens is popped
//      else // t is an operator or left parens
//          pop and output tokens until one of lower priority is encounted or left parnes
//          or the stack is empty
//          push t
// pop and output tokens until stack empty
//

int priority(char x) {
    if (x == '(') {
        return 0;
    } else if (x == '+' || x == '-') {
        return 1;
    } else if (x == '*' || x == '/') {
        return 2;
    }

    return 3;
}

char *infixToPostfix(char *e, char *res) {
    char x;
    int *stack = (int*)malloc(10 * sizeof(int));
    int top = -1;
    int count = 0;

    while (*e != '\0') {
        if (*e == ' ') {
            e++;
            continue;
        } else if (isalnum(*e)) {
            res[count++] = *e;
        } else if (*e == '(') {
            stack[++top] = *e;
        } else if (*e == ')') {
            // pop until matching left paren
            while (top > -1 && (x = stack[top--]) != '(') {
                res[count++] = x;
            }
        } else {
            // pop based on priority (stack higher priority gets output)
            while (top > -1 && priority(stack[top]) >= priority(*e)) {
                res[count++] = stack[top--];
            }
            // then push to stack
            stack[++top] = *e;
        }
        e++;
    }

    while (top > -1) {
        res[count++] = stack[top--];
    }

    free(stack);
    res[count++] = '\0';
    return realloc(res, count);
}

int main() {
    char *a = "(a+(b*(d+2)))";
    char *res = malloc(strlen(a));
    char *exp = "abd2+*+";

    char *a2 = "a * b - (c + d) + e";
    char *res2 = malloc(strlen(a2));
    char *exp2 = "ab*cd+-e+";

    res = infixToPostfix(a, res);
    res2 = infixToPostfix(a2, res2);
    assert(strcmp(res, exp) == 0);
    assert(strcmp(res2, exp2) == 0);

    free(res2);
    free(res);
}

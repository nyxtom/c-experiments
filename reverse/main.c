#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strrev(char *str) {
    int len = strlen(str);

    int temp;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

char *reverse(char *str) {
    int len = strlen(str);
    char *r = (char*) malloc(sizeof(str));
    int i = len - 1;
    int k = 0;
    for(; i >= 0; i--) {
        r[k] = str[i];
        k++;
    }

    return r;
}

int stoi(char *s) {
    int i = 0, n = 0;

    for (; s[i] >= '0' && s[i] <= '9'; i++) {
        n = n * 10 + (s[i] - '0');
    }

    return n;
}

int main() {
    char str[] = "Hello";
    printf("%s\n", str);
    strrev(str);
    printf("%s\n", str);
    printf("%s\n", reverse("foo"));
    printf("%d", stoi("321"));
}

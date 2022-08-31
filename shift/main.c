#include <stdio.h>
int main() {
    char z = 'z';
    char a = (z + 1);
    if (a > 'z') {
        a = 'a';
    }
    printf("%c", a);
    return 0;
}

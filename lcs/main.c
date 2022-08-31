#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int max(a, b) {
    return a > b ? a : b;
}

int main() {
    // given two strings, find the longest common substring
    char *a = "abcbdab";
    char *b = "bdcaba";

    int r = strlen(a);
    int c = strlen(b);
    int *arr = malloc(r * c * sizeof(int));
    memset(arr, 0, (r * c) * sizeof(*arr));

    int m = 0;
    int fj = -1;
    int fi = -1;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (a[i] == b[j]) {
                int offset = i * c + j;
                arr[offset] += arr[max(i - 1, 0) * c + max(j - 1, 0)] + 1;
                if (m < arr[offset]) {
                    fj = j;
                    fi = i;
                }
                m = max(arr[offset], m);
            }
        }
    }

    printf("%d\n(%d, %d)\n", m, fi - m + 1, fj - m + 1);
    int j = fj - m + 1;
    for (int i = 0; i < m; i++) {
        printf("%c", b[j + i]);
    }
    printf("\n");

    free(arr);
    return 0;
}

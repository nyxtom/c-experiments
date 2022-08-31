#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *lps(char *pattern, int *partial, int len) {
    partial[0] = 0;

    int j = 0;
    for (int i = 1; i < len; i++) {
        j = partial[i - 1];
        while (j > 0 && pattern[j] != pattern[i]) {
            j = partial[j - 1];
        }

        if (pattern[j] == pattern[i]) {
            partial[i] = j + 1;
        } else {
            partial[i] = j;
        }
    }

    return partial;
}

int *kpm(char *input, char *pattern) {
    int len = strlen(pattern);
    int input_len = strlen(input);
    int count = 0;
    int *res = calloc(input_len, sizeof(int));
    int *table = calloc(len, sizeof(int));
    table = lps(pattern, table, len);

    int j = 0;
    for (int i = 0; i < input_len; i++) {
        char c = input[i];
        while (j > 0 && c != pattern[j]) {
            j = table[j - 1];
        }

        if (c == pattern[j]) {
            j += 1;
        }
        if (j == len) {
            res[count++] = i + 1 - j;
            j = table[j - 1];
        }
    }

    free(table);
    res = realloc(res, count * sizeof(int));
    return res;
}

void assert_arr(int *arr, int *exp, int len) {
    for (int i = 0; i < len; i++) {
        assert(arr[i] == exp[i]);
    }
}

int main() {
    int *res = kpm("aaa", "a");
    int exp[] = {0, 1, 2};
    assert_arr(res, exp, 3);

    free(res);

    res = kpm("abababa", "ab");
    int exp2[] = {0, 2, 4};
    assert_arr(res, exp2, 3);

    free(res);

    return 0;
}

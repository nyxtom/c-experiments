#include <stdio.h>

void rotate(int **arr, int n) {
    int i = 0;
    int k = n - 1;

    while (i < k) {
        int *ai = arr[i];
        int *aj = arr[k];
        arr[i] = aj;
        arr[k] = ai;
        i += 1;
        k -= 1;
    }

    i = 0;
    for (; i < n; i++) {
        for (k = i + 1; k < n; k++) {
            int ik = arr[i][k];
            int ki = arr[k][i];
            arr[i][k] = ki;
            arr[k][i] = ik;
        }
    }
}

int main() {
    int *arr[3];
    int aa[3] = {1,2,3},
        ab[3] = {4,5,6},
        ac[3] = {7,8,9};
    arr[0] = aa;
    arr[1] = ab;
    arr[2] = ac;

    rotate(arr, 3);

    for (int i = 0; i < 3; i++) {
        printf("[");
        for (int j = 0; j < 3; j++) {
            printf("%d", arr[i][j]);
        }
        printf("]\n");
    }
    return 0;
}

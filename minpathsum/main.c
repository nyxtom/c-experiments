#include <assert.h>

int minPathSum(int** grid, int m, int* n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < *n; j++) {
            int u = i == 0 ? 0 : grid[i - 1][j];
            int l = j == 0 ? 0 : grid[i][j - 1];
            int m = 0;
            if (i == 0) {
                m = l;
            } else if (j == 0) {
                m = u;
            } else {
                m = l < u ? l : u;
            }
            grid[i][j] = grid[i][j] + m;
        }
    }

    return grid[m-1][*n-1];
}

int main() {
    int *arr[3];
    int aa[] = {1,3,1},
        ab[] = {1,5,1},
        ac[] = {4,2,1};
    arr[0] = aa;
    arr[1] = ab;
    arr[2] = ac;
    int **ptr = arr;
    int n = 3;
    assert(minPathSum(ptr, 3, &n) == 7);
    return 0;
}

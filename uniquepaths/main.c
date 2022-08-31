#include <math.h>
#include <stdio.h>
#include <assert.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int uniquePaths(int** grid, int m, int n) {
    if (grid[0][0] == 1) return 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) grid[i][j] = 1; // starting position
            else if (grid[i][j] == 1) grid[i][j] = 0; // found obstacle
            else grid[i][j] = grid[max(i - 1, 0)][j] + grid[i][max(j - 1, 0)]; // top + left
        }
    }

    return grid[m-1][n-1];
}

int main() {
    int *arr[3];
    int aa[] = {0,0,0},
        ab[] = {0,1,0},
        ac[] = {0,0,0};
    arr[0] = aa;
    arr[1] = ab;
    arr[2] = ac;
    int **ptr = arr;
    assert(uniquePaths(ptr, 3, 3) == 2);
    return 0;
}



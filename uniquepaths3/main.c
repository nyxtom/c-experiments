
int dfs(int** grid, int x, int y, int zero, int gridSize, int gridColSize) {
    if (x < 0 || y < 0 || x >= gridSize || y >= gridColSize || grid[x][y] == -1) {
        return 0;
    }
    if (grid[x][y] == 2) {
        return zero == -1 ? 1 : 0;
    }
    grid[x][y] = -1;
    zero--;
    
    int totalPaths = dfs(grid, x + 1, y, zero, gridSize, gridColSize) +
        dfs(grid, x, y + 1, zero, gridSize, gridColSize) +
        dfs(grid, x - 1, y, zero, gridSize, gridColSize) + 
        dfs(grid, x, y - 1, zero, gridSize, gridColSize);
    
    grid[x][y] = 0;
    zero++;
    
    return totalPaths;
}

int uniquePathsIII(int** grid, int gridSize, int* gridColSize){
    int zero = 0, sx = 0, sy = 0;
    
    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < *gridColSize; c++) {
            if (grid[r][c] == 0) zero++;
            else if (grid[r][c] == 1) {
                sx = r;
                sy = c;
            }
        }
    }
    
    return dfs(grid, sx, sy, zero, gridSize, *gridColSize);
}


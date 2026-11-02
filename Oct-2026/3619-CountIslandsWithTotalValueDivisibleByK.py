from typing import List


class Solution:
    def __init__(self):
        self.k: int = 0
        self.m: int = 0
        self.n: int = 0
        self.visited: List[List[bool]] = []

    def countIslands(self, grid: List[List[int]], k: int) -> int:
        self.m = len(grid)
        self.n = len(grid[0])
        self.k = k
        self.visited = [[False for _ in range(self.n)] for _ in range(self.m)]
        count = 0
        for i in range(self.m):
            for j in range(self.n):
                if (grid[i][j] != 0 and not self.visited[i][j]):
                    count += self.dfs(i, j, grid) % k == 0
        return count

    def dfs(self, i: int, j: int, grid: List[List[int]]) -> int:
        if (i < 0 or i >= self.m or j < 0 or j >= self.n
            or grid[i][j] == 0 or self.visited[i][j]):
            return 0

        self.visited[i][j] = True 
        return (grid[i][j] 
            + self.dfs(i+1, j, grid)
            + self.dfs(i-1, j, grid)
            + self.dfs(i, j+1, grid)
            + self.dfs(i, j-1, grid)) % self.k
            

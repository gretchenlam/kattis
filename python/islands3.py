from collections import deque

def min_islands():
    rows, cols = map(int, input().split())
    grid = []
    for x in range(rows):
        grid.append(input())

    visited = []
    for x in range(rows):
        row = [False] * cols
        visited.append(row)
        
    land_location = set()
    for y in range(rows):
        for x in range(cols):
            if grid[y][x] == 'L':
                land_location.add((x,y))

    def is_potential_land(r, c):
        if grid[r][c] == 'L':
            return True
        if grid[r][c] == 'C':
            if (r > 0 and grid[r-1][c] == 'L') or (r < rows - 1 and grid[r+1][c] == 'L') or (c > 0 and grid[r][c-1] == 'L') or (c < cols - 1 and grid[r][c+1] == 'L') or (r > 0 and grid[r-1][c] == 'C') or (r < rows - 1 and grid[r+1][c] == 'C') or (c > 0 and grid[r][c-1] == 'C') or (c < cols - 1 and grid[r][c+1] == 'C'):
                return True
        return False

    def bfs(c, r):
        queue = deque([(r, c)])
        visited[c][r] = True

        while queue:
            x, y = queue.popleft()
            if y >= 1 and not visited[y-1][x] and is_potential_land(y-1, x):
                visited[y-1][x] = True
                queue.append((x, y-1))
            if y < rows - 1 and not visited[y+1][x] and is_potential_land(y+1, x):
                visited[y+1][x] = True
                queue.append((x, y+1))
            if x >= 1 and not visited[y][x-1] and is_potential_land(y, x-1):
                visited[y][x-1] = True
                queue.append((x-1, y))
            if x < cols - 1 and not visited[y][x+1] and is_potential_land(y, x+1):
                visited[y][x+1] = True
                queue.append((x+1, y))

    islands = 0
    for (x,y) in land_location:
        if not visited[y][x]:
            bfs(y, x)
            islands += 1

    return islands

print(min_islands())
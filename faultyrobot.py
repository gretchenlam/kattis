def stopping_points():
    n, m = map(int, input().split())
    edges = []
    for _ in range(m):
        edge = tuple(map(int, input().split()))
        edges.append(edge)

    graph = {x : [] for x in range(1, n+1)} 
    forced_moves = {x : [] for x in range(1, n+1)}

    for (start, end) in edges:
        graph[abs(start)].append(end)
        if start < 0:
            forced_moves[abs(start)].append(end)

    queue = []
    visited = [] 
    for _ in range(n + 1):
        visited.append([False] * (2)) 
    
    queue.append((1, 0))
    visited[1][0] = True 

    stop = set()

    while queue:
        node, bug_move_made = queue.pop()
        if not forced_moves[node]: # if node has no forced moves
            stop.add(node)
        if bug_move_made == 0: # if no bug move made
            for neighbor in graph[node]:
                if visited[neighbor][1] == False: # if the neighboring node has also not been visited with a bug move made
                    visited[neighbor][1] = True # bug move made on neighbor
                    queue.append((neighbor, 1)) # explore that neighbor with bug move made
        for neighbor in forced_moves[node]:
            if visited[neighbor][bug_move_made] == False: # check if neighboring node has not been visited yet in current bug move state
                visited[neighbor][bug_move_made] = True # now visited
                queue.append((neighbor, bug_move_made))
    
    return len(stop)

stop = stopping_points()
print(stop)
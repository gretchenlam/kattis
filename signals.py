def update(index, value, tree, N):
    pos = index + N
    tree[pos] = value # updates leaves index
    while pos > 1:
        pos //= 2 # find parent of whatever node we at
        tree[pos] = max(tree[2 * pos], tree[2 * pos + 1])

def build_tree(p):
    N = 1
    while N < p + 2:
        N *= 2
    tree = [0] * 2 * N  
    return tree, N

def query(l, r, tree, N):
    res = 0  
    l += N
    r += N

    while l < r:
        if l % 2 == 1:
            res = max(res, tree[l])
            l += 1
        if r % 2 == 1:  
            r -= 1
            res = max(res, tree[r])
        l //= 2 
        r //= 2 

    return res

def max_signals(signal_mappings, tree, N):
    for i, signal in enumerate(signal_mappings):
        max_signals_before = query(0, signal, tree, N)
        update(signal, max_signals_before + 1, tree, N)
    return query(0, N, tree, N)

p = int(input())
signal_mappings = []
for _ in range(p):
    signal_mappings.append(int(input()) - 1)
tree, N = build_tree(p)

result = max_signals(signal_mappings, tree, N)

print(result)
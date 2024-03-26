def update(tree, N, index, value):
    pos = index + N
    tree[pos] += value 
    while pos > 1:
        pos //= 2
        tree[pos] = tree[2 * pos] + tree[2 * pos + 1]  

def build_tree(n):
    N = 1
    while N < n + 2:
        N *= 2
    tree = [0] * (2 * N)
    return tree, N

def query(tree, N, l, r):
    res = 0
    l += N
    r += N

    while l < r:
        if l % 2 == 1:
            res += tree[l]
            l += 1
        if r % 2 == 1:
            r -= 1
            res += tree[r]
        l //= 2
        r //= 2

    return res

def calculate_non_inversions(bet, index_map, n):
    tree, N = build_tree(n)
    non_inversions = 0
    for camel in bet:
        non_inversions += query(tree, N, 0, index_map[camel])
        update(tree, N, index_map[camel], 1) # seen
    return non_inversions

n = int(input())
bets = []
for _ in range(3):
    bets.append(list(map(int, input().split())))


inv_maps = []
for bet in bets:
    index_map = {}
    for index, camel in enumerate(bet):
        index_map[camel] = index
    inv_maps.append(index_map)


non_inversions = []
non_inversions.append(calculate_non_inversions(bets[0], inv_maps[1], n))
non_inversions.append(calculate_non_inversions(bets[1], inv_maps[2], n))
non_inversions.append(calculate_non_inversions(bets[2], inv_maps[0], n))

total_pairs = n * (n - 1) // 2 # n choose 2
consistent_pairs = (sum(non_inversions) - total_pairs) // 2 # counts once for each bet where inverted so 2

print(consistent_pairs)
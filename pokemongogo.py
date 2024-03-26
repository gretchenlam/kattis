def calculate_distance(p1, p2):
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

def solve(current, caught_mask, pokestops, memo, pokemon_indices, unique_count):
    if caught_mask == (1 << unique_count) - 1 and current == 0:
        return 0

    if (current, caught_mask) in memo:
        return memo[(current, caught_mask)]

    min_distance = float('inf')
    for i, ((x, y), pokemon) in enumerate(pokestops):
        if i != current:
            next_caught_mask = caught_mask
            if pokemon.lower() in pokemon_indices: 
                next_caught_mask |= 1 << pokemon_indices[pokemon.lower()]

            if next_caught_mask != caught_mask or (i == 0 and caught_mask == (1 << unique_count) - 1):
                dist_to_next = calculate_distance(pokestops[current][0], (x, y))
                total_distance = dist_to_next + solve(i, next_caught_mask, pokestops, memo, pokemon_indices, unique_count)
                min_distance = min(min_distance, total_distance)

    memo[(current, caught_mask)] = min_distance
    return min_distance

n = int(input())
pokestops = []
pokestops.append(((0, 0), 'Origin'))
pokemon_indices = {}
unique = set()

for _ in range(n):
    x, y, pokemon_name = input().strip().split()
    pokemon_name = pokemon_name.lower()
    if pokemon_name not in unique:
        pokemon_indices[pokemon_name] = len(unique)
        unique.add(pokemon_name)
    pokestops.append(((int(x), int(y)), pokemon_name))

memo = {}
ans = solve(0, 0, pokestops, memo, pokemon_indices, len(unique))
print(ans)
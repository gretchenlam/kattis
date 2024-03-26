villagers = int(input())
evenings = int(input())
villager_sets = [set() for _ in range(villagers)]

for x in range(evenings):
    entry = [int(i) for i in input().split()]
    num_villagers_present = entry[0]
    present_villagers_id = entry[1:]

    if 1 in present_villagers_id:
        for id in present_villagers_id:
            villager_sets[id-1].add(x+1)
    else:
        union_set = set().union(*[villager_sets[i-1] for i in present_villagers_id])

        for id in present_villagers_id:
            villager_sets[id-1] = union_set.copy()


ans = []
bard_length = len(villager_sets[0])
for i,j in enumerate(villager_sets):
    if len(j) == bard_length:
        ans.append(i+1)
ans = sorted(ans)
print(*ans)
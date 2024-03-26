def min_height_cloud(entries, num_entries, max_width):
    dp = [] # dp[x] store min height needed to arrange first x entries given max width
    dp.append(0) # no entries yet, 0 height
    for _ in range(1, num_entries + 1):  # 1 to n
        dp.append(float('inf')) 

    for i in range(num_entries): # i is possible start in new row
        total_width = 0  
        max_height = 0 # tallest entry in curr row = max height

        for j in range(i, num_entries):
            total_width += entries[j][0]
            max_height = max(max_height, entries[j][1])

            if total_width > max_width:
                break
            dp[j + 1] = min(dp[j + 1], dp[i] + max_height) # dp[0] = 0, so if j = 0 then must use dp[j + 1]

    return dp[num_entries]


num_entries, max_width = map(int, input().split())

entries = []
for _ in range (num_entries):
    entries.append(tuple(map(int, input().split())))

ans = min_height_cloud(entries, num_entries, max_width)
print(ans)
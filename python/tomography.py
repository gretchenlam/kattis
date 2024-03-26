def solve(rows, cols, row_sums, col_sums):

    # go row by row
    for i in range(rows):
        # column indices sorted by descending sums
        key_func = lambda k: col_sums[k]
        sorted_cols = sorted(range(cols), key=key_func, reverse=True)

        ones_needed = row_sums[i]  # num of 1s needed in the current row

        for col_index in sorted_cols:
            if ones_needed > 0 and col_sums[col_index] > 0:
                ones_needed -= 1
                col_sums[col_index] -= 1
        
        # not all 1s needed for the row could be placed
        if ones_needed > 0:
            return False

    # after placing 1s for all rows, check if any column sums not yet met
    if any(col_sums):
        return False

    return True

rows, cols = map(int, input().split())
row_sums = list(map(int, input().split()))
col_sums = list(map(int, input().split()))

if solve(rows, cols, row_sums, col_sums):
    print("Yes")
else:
    print("No")
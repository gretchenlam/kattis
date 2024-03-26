while True:
    n = int(input())
    if n == 0:
        break

    last_names = []
    for _ in range(n):
        last_names.append(input())

    key_func = lambda x: x[:2]
    
    last_names.sort(key=key_func)

    for name in last_names:
        print(name)
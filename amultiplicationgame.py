# no matter what the first player picks, the second player can pick 9 and they will be over 17. Therefore, ollie wins.
from sys import stdin

for n in stdin:
    n = int(n)
    stan = True
    ollie = False
    p = 1
    while p < n:
        if stan:
            p *= 9
        elif ollie:
            p *= 2
        if p >= n:
            if stan:
                print("Stan wins.")
                break
            if ollie:
                print("Ollie wins.")
                break
        stan = not stan
        ollie = not ollie
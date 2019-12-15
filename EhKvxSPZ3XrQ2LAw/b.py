n, m = map(int, input().split())
d = [[0 for i in range(2)] for j in range(n + 2)]

for _ in range(m):
    l, r, s, e = map(int, input().split())
    toler = (e - s) // (r - l)
    d[l + 1][1] += toler
    d[r + 1][1] -= toler
    d[l][0] += s
    d[r + 1][0] -= e

for i in range(1, n + 1):
    d[i][1] += d[i - 1][1]
    d[i][0] += d[i][1]

ans = 0
for i in range(1, n + 1):
    d[i][0] += d[i - 1][0]
    ans ^= d[i][0]

print(ans)

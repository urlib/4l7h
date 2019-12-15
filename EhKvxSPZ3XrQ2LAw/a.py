n = int(input())
a = [int(_) for _ in input().split()]
dp = [0] * n
Dp = [0] * n

tmp = 0
mx = 0
for i in range(n):
    tmp += a[i]
    if tmp < 0:
        tmp = 0
    else:
        mx = max(mx, tmp)
    dp[i] = mx

tmp = 0
mx = 0
a.reverse()
for i in range(n):
    tmp += a[i]
    if tmp < 0:
        tmp = 0
    else:
        mx = max(mx, tmp)
    Dp[i] = mx

ans = 0
for i in range(n):
    ans = max(ans, dp[i] + Dp[n - i - 1])
print(ans)

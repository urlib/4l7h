#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#include "bits/stdc++.h"
#define mem(x) memset((x), 0, sizeof((x)))
#define il __attribute__((always_inline))
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#if __cplusplus > 201403L
#define r
#else
#define r register
#endif
#define ri r int
#define rl r ll
#define c const
namespace _c
{
c double pi = acos(-1.0); // PI
namespace min
{
c int i8 = -128;
c int i16 = -32768;
c int i = -2147483647 - 1;
c ll l = -9223372036854775807LL - 1;
} // namespace min
namespace max
{
c int i8 = 127;
c int i16 = 32767;
c int i = 2147483647;
c ll l = 9223372036854775807LL;
} // namespace max
} // namespace _c
namespace _f
{
template <typename T> // return gcd
inline c T gcd(T m, T n)
{
    while (n != 0)
    {
        T t = m % n;
        m = n;
        n = t;
    }
    return m;
}
template <typename T>
inline c T max(c T &a, c T &b)
{
    return a > b ? a : b;
}
template <typename T>
inline c T min(c T &a, c T &b)
{
    return a < b ? a : b;
}
template <typename T>
inline c T abs(c T &a)
{
    return a > 0 ? a : -a;
}
template <typename T>
inline T pow(T a, T b)
{
    T res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}
template <typename T>
inline T pow(T a, T b, c T &m)
{
    a %= m;
    T res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = res * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return res % m;
}
} // namespace _f
namespace io
{
template <typename T>
inline void read(T &t)
{
    r T res = 0, neg = 1;
    char g = getchar();
    for (; !isdigit(g); g = getchar())
    {
        if (g == '-')
        {
            neg = -1;
        }
    }
    for (; isdigit(g); g = getchar())
    {
        res = res * 10 + g - '0';
    }
    t = res * neg;
}
#if __cplusplus >= 201103L
template <typename T, typename... Args>
void read(T &x, Args &... args)
{
    read(x);
    read(args...);
}
#endif
inline int in()
{
    ri T;
    read(T);
    return T;
}
inline ll in_ll()
{
    rl T;
    read(T);
    return T;
}
} // namespace io
#undef c
#undef r

const int N = 40;
const int MOD = 1e9 + 7;
int n, ans = 0, tag = 0;
int a[N + 5];
int dp[2][N + 5][(N + 5) * (N + 5)][2];

inline void add(int &a, const int &b)
{
    (a += b) %= MOD;
}

int main()
{
    io::read(n);
    for (int i = 1; i <= n; i++)
    {
        io::read(a[i]);
    }

    if (a[1] == -1)
    {
        for (int i = 0; i <= 40; i++)
        {
            dp[0][i][i][0] = 1;
        }
    }
    else
    {
        dp[0][a[1]][a[1]][0] = 1;
    }

    for (int i = 2; i <= n; i++)
    {
        tag ^= 1;
        memset(dp[tag], 0, sizeof(dp[tag]));
        if (a[i] == -1)
        {
            for (int j = 0; j <= N; j++)
            {
                for (int k = j * (i - 1); k <= N * N; k++)
                {
                    for (int l = 0; l <= N; l++)
                    {
                        if (l > j)
                        {
                            add(dp[tag][j][k + j][1], dp[tag ^ 1][l][k][0]);
                        }
                        else
                        {
                            add(dp[tag][j][k + j][0], (dp[tag ^ 1][l][k][0] + dp[tag ^ 1][l][k][1]) % MOD);
                        }
                    }
                }
            }
        }
        else
        {
            int j = a[i];
            for (int k = j * (i - 1); k <= N * N; k++)
            {
                for (int l = 0; l <= N; l++)
                {
                    if (l > j)
                    {
                        add(dp[tag][j][k + j][1], dp[tag ^ 1][l][k][0]);
                    }
                    else
                    {
                        add(dp[tag][j][k + j][0], (dp[tag ^ 1][l][k][0] + dp[tag ^ 1][l][k][1]) % MOD);
                    }
                }
            }
        }
    }

    if (a[n] == -1)
    {
        for (int j = 0; j <= N; j++)
        {
            for (int k = 0; k <= N * N; k++)
            {
                add(ans, dp[tag][j][k][0]);
                add(ans, dp[tag][j][k][1]);
            }
        }
    }
    else
    {
        int j = a[n];
        for (int k = 0; k <= N * N; k++)
        {
            add(ans, dp[tag][j][k][0]);
            add(ans, dp[tag][j][k][1]);
        }
    }
    printf("%d\n", ans);
}
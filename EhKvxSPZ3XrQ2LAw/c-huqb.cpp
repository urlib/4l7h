#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int n, a[45], dp[2][45][1605][2]; //dp[i][j][k][l]表示到第i个，上一个为j，总和为k.连续下降l个

// 计算鸭喜欢序列，他认为如下的序列是可爱的

// 1：序列中的元素大于等于0小于等于40

// 2：序列中每个元素都不大于之前的数的平均值

// 3：没有三个连续的递减的数

// 有一个序列a[].(−1 ≤ a[i] ≤ 40)

// 你可以将-1变成任意整数，求a序列可以变成多少不同的可爱序列，答案对 1e9+7 取模

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int tmp = 0;
    if (a[1] == -1)
        for (int i = 0; i <= 40; i++)
            dp[0][i][i][0] = 1;
    else
        dp[0][a[1]][a[1]][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        tmp ^= 1;
        memset(dp[tmp], 0, sizeof(dp[tmp]));
        if (a[i] == -1)
        {
            for (int j = 0; j <= 40; j++)
                for (int k = j * (i - 1); k <= 40 * 40; k++)
                    for (int l = 0; l <= 40; l++)
                    {
                        if (l > j)
                            dp[tmp][j][k + j][1] += dp[tmp ^ 1][l][k][0], dp[tmp][j][k + j][1] %= mod;
                        else
                            dp[tmp][j][k + j][0] += (dp[tmp ^ 1][l][k][0] + dp[tmp ^ 1][l][k][1]) % mod, dp[tmp][j][k + j][0] %= mod;
                    }
        }
        else
        {
            int j = a[i];
            for (int k = j * (i - 1); k <= 40 * 40; k++)
                for (int l = 0; l <= 40; l++)
                {
                    if (l > j)
                        dp[tmp][j][k + j][1] += dp[tmp ^ 1][l][k][0], dp[tmp][j][k + j][1] %= mod;
                    else
                        dp[tmp][j][k + j][0] += (dp[tmp ^ 1][l][k][0] + dp[tmp ^ 1][l][k][1]) % mod, dp[tmp][j][k + j][0] %= mod;
                }
        }
    }
    int ans = 0;
    if (a[n] == -1)
    {
        for (int j = 0; j <= 40; j++)
            for (int k = 0; k <= 1600; k++)
                ans = (ans + dp[tmp][j][k][0]) % mod, ans = (ans + dp[tmp][j][k][1]) % mod;
    }
    else
    {
        int j = a[n];
        for (int k = 0; k <= 1600; k++)
            ans = (ans + dp[tmp][j][k][0]) % mod, ans = (ans + dp[tmp][j][k][1]) % mod;
    }
    cout << ans << endl;
}
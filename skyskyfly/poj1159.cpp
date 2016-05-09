题目大意：给你一个字符串，让你往其中插入字符，使其变成回文字符串，问最少需要插入多少字符。
思路分析：所谓回文字符串，就是正读和倒读一样的，因此可以考虑构造两个字符串，另一个字符串是
原字符串的逆序串，然后求最长公共子序列长度，那么字符串长度减去最长公共字符串长度就是需要插入
的字符数。
代码：
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
const int maxn=5000+100;
short dp[maxn][maxn];
int main()
{
    int n;
    char s1[maxn],s2[maxn];
    scanf("%d",&n);
       cin>>s1;
       for(int i=n-1;i>=0;i--)
        s2[n-i-1]=s1[i];
       memset(dp,0,sizeof(dp));
       for(int i=0;i<n;i++)
       {
           for(int j=0;j<n;j++)
           {
               if(s1[i]==s2[j])
               {
                   if(i>=1&&j>=1)
                    dp[i][j]=dp[i-1][j-1]+1;
                   else dp[i][j]=1;
               }
               if(s1[i]!=s2[j])
               {
                   if(i==0&&j==0) dp[0][0]=0;
                   else if(i>=1&&j==0) dp[i][j]=dp[i-1][j];
                   else if(i==0&&j>=1) dp[i][j]=dp[i][j-1];
                   else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
               }
           }
       }
       cout<<(n-dp[n-1][n-1])<<endl;
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
const int maxn1=1000+10;
const int maxn2=30+5;
int dp[maxn1][maxn2];//dp[i][j]代表的是前imin，移动j次可以捡到的最大苹果数
int num[maxn1];
const int inf=0xffffff;
int main()
{
     int t,w;
     while(scanf("%d%d",&t,&w)!=EOF)
     {
         memset(dp,0,sizeof(dp));
        for(int i=1;i<=t;i++)
            scanf("%d",&num[i]);
        if(num[1]==1) dp[1][0]=1,dp[1][1]=0;
        else dp[1][0]=0,dp[1][1]=1;
        for(int i=2;i<=t;i++)
        {
            for(int j=0;j<=w;j++)
            {
                if(j==0) dp[i][j]=dp[i-1][j]+(num[i]==1);
                else
                {
                    dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
                    if(j%2+1==num[i]) dp[i][j]++;
                }
            }
        }
        int ma=-inf;
        for(int i=1;i<=t;i++)
            for(int j=0;j<=w;j++)
            if(dp[i][j]>ma) ma=dp[i][j];
        cout<<ma<<endl;
     }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <map>
using namespace std;
const int maxn=100000+100;
int a[maxn];
int n,c;
bool check(int dis)
{
    int last=0;
    for(int i=1;i<c;i++)//放置c头牛，共有c-1个空
    {
        int next=last+1;//next初始化
        while(next<n&&a[next]-a[last]<dis) next++;//直到寻找到满足条件的next:
        if(next>=n) return false;
        last=next;//更新last
    }
    return true;
}
int main()
{
    int ans;
    while(scanf("%d%d",&n,&c)!=EOF)
    {
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        sort(a,a+n);//使用二分逼近的方法确定答案，首先必须保证数组单调
        int l=0,r=a[n-1]+1;//枚举的是距离，范围是0~a[n-1]+1;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid)) ans=mid,l=mid+1;//满足条件，更新答案。
            else r=mid-1;
        }
        printf("%d\n",ans);
    }
	return 0;
}

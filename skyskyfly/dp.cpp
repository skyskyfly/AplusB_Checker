#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
const int maxn=50000+100;
int a[maxn],t1[maxn],t2[maxn],l[maxn],r[maxn];
const int inf=-1000001;
int main()
{
        int T;
        scanf("%d",&T);
        while(T--)
        {
            int n;
            scanf("%d",&n);
            for(int i=1;i<=n;i++)
            {
                scanf("%d",&a[i]);
            }
            memset(t1,0,sizeof(t1));
            memset(t2,0,sizeof(t2));
            for(int i=1;i<=n;i++)
            {
                t1[i]=max(t1[i-1]+a[i],a[i]);
            }
            for(int i=n;i>=1;i--)
            {
                t2[i]=max(t2[i+1]+a[i],a[i]);
            }
            l[1]=a[1];
            for(int i=2;i<=n;i++)
            {
                l[i]=max(l[i-1],t1[i]);
            }
           r[n]=a[n];
           for(int i=n-1;i>=1;i--)
           {
               r[i]=max(r[i+1],t2[i]);
           }
           int ma=inf;
           for(int i=2;i<=n;i++)
           {
               int t=l[i-1]+r[i];
               ma=max(ma,t);
           }
           cout<<ma<<endl;
        }
     return 0;
}

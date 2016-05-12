#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#define mem(a) memset(a,0,sizeof(a))
using namespace std;
const int inf=0xffffff;
const int maxn=4000+10;
int a[maxn],b[maxn],c[maxn],d[maxn];
int f1[maxn*maxn],f2[maxn*maxn];
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int cut=0;
        for(int i=0;i<n;i++)
            scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                f1[i*n+j]=a[i]+b[j];
                f2[i*n+j]=c[i]+d[j];
            }
        }
        sort(f2,f2+n*n);
    for(int i=0;i<n*n;i++)
    {
        int low=0,high=n*n-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(f2[mid]==-f1[i])
        {
             cut++;
             for(int j=mid-1;j>=0;j--)
             {
                 if(f2[j]!=-f1[i]) break;
                 cut++;
             }
             for(int j=mid+1;j<n*n;j++)
             {
                  if(f2[j]!=-f1[i]) break;
                 cut++;
             }
             break;
        }
      else if(f2[mid]<-f1[i]) low=mid+1;
      else high=mid-1;
    }
    }
    cout<<cut<<endl;
    }
    return 0;
}

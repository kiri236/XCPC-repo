#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6;
typedef pair<int, int> PII;
int p[N];
int sz[N];
int color[N];
int colorsz[N];
PII pos[N];
int find(int x)
{
    if(x!=p[x])p[x]=find(p[x]);
    return p[x];
}
int main()
{
    int n;
    scanf("%d", &n);
    int q;
    scanf("%d", &q);
    for(int i = 1;  i<= n ; i ++)
    {
        p[i] = i ;
        color[i] = i ;
        colorsz[i] = 1;
        sz[i] = 1;
        pos[i]={i,i};
    }
    pos[n+1] = {n+1,n+1};
    pos[0] = {0,0};
    while(q--)
    {
        int op;
        scanf("%d", &op);
        if(op==1)
        {
            int x,c;
            scanf("%d", &x);
            scanf("%d", &c);
            int u = find(x);
            int r = pos[u].second, l = pos[u].first;
            int pre = l;
            colorsz[color[u]]-=sz[u];
            while(l>=1&&color[find(l)]==color[u])
            {
                int v = find(l);
                if(u!=v)
                {
                    p[v] = u;
                    colorsz[color[v]] -= sz[v];
                    sz[u] += sz[v];
                    sz[v] = 0;
                }
                pre = l;
                l = pos[l-1].first;
            }
            l = pre;
            pre = r ;
            while(r<=n&&color[find(r)]==color[u])
            {
                int v = find(r);
                
                if(u!=v)
                {
                    p[v] = u;
                    colorsz[color[v]] -= sz[v];
                    sz[u] += sz[v];
                    sz[v] = 0 ;
                }
                //cout << r << endl;
                pre = r;
                r = pos[r+1].second;
            }
            r = pre;
            pos[u] = {l,r};
            color[u] = c;
            //cout << sz[u] << ' ' << colorsz[c] << endl;
            colorsz[c] += sz[u];
        }else 
        {
            int c;
            scanf("%d", &c);
            cout << colorsz[c] << endl;
        }
    }
}
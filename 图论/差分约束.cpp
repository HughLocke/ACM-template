/*差分约束系统：如果一个系统由n个变量和m个约束条件组成，其中每个约束条件形如 xj - xi<= bk ( i , j ∈ [1，n]，k ∈ [1，m])，则称其为差分约束系统。 
例如如下的约束条件： 
X1 - X2 <= 0 X1 - X5 <= -1 
X2 - X5 <= 1 X3 - X1 <= 5 
X4 - X1 <= 4 X4 - X3 <= -1 
X5 - X3 <= -3 X5 - X4 <= -3 
全都是两个未知数的差小于等于某个常数（大于等于也可以，因为左右乘以-1就可以化成小于等于）。这样的不等式组就称作差分约束系统。 
差分约束系统求解过程： 
1.新建一个图，N个变量看作N个顶点，M个约束条件作为M条边。每个顶点Vi分别对于一个未知量，每个有向边对应两个未知量的不等式。 
2.为了保证图的连通性，在图中新加一个节点Vs，图中每个节点Vi都能从Vs可达，建立边w(Vs，Vi) = 0。 
3.对于每个差分约束Xj - Xi <= Bk(这里是小于等于号)，则建立边w(Xi，Xj) = Bk。 
4.初始化Dist[] = INF，Dist[Vs] = 0. 
5.求解以Vs为源点的单源最短路径，推荐用SPFA，因为一般可能存在负值。 
如果图中存在负权回路，则该差分约束系统不存在可行解。 
Vs到某点如果不存在最短路径，即最短路为INF，则对于该点表示的变量可以取任意值，都能满足差分约束的要求，如果存在最短路径，则得到该变量的最大值。 
上述过程最终得到的解为满足差分约束系统各项的最大值。 
注意点： 
1. 如果要求最大值想办法把每个不等式变为标准 x - y <= k 的形式,然后建立一条从 y 到 x 权值为 k 的边，变得时候注意 x - y < k => x - y <= k-1。 
2. 如果要求最小值的话，变为 x - y >= k 的标准形式，然后建立一条从 y到 x 权值为 k 的边，求出最长路径即可。 
3. 如果权值为正，用Dijkstra，SPFA，BellmanFord都可以，如果为负不能用Dijkstra，并且需要判断是否有负环，有的话就不存在。*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;
const int MAXN = 1100;
const int MAXM = 30030;

struct EdgeNode
{
    int to;
    int w;
    int next;
}Edges[MAXM];

int Head[MAXN],Dist[MAXN],vis[MAXN],outque[MAXN],id;

void AddEdges(int u,int v,int w)
{
    Edges[id].to = v;
    Edges[id].w = w;
    Edges[id].next = Head[u];
    Head[u] = id++;
}
void SPFA(int s,int N)
{
    int ans = 0;
    memset(vis,0,sizeof(vis));
    memset(outque,0,sizeof(outque));
    for(int i = 1; i <= N; ++i) Dist[i] = INF;
    Dist[s] = 0;
    vis[s] = 1;
    queue<int> Q;
    Q.push(s);
    while( !Q.empty() )
    {
        int u = Q.front();
        Q.pop();
        vis[u] = 0;
        outque[u]++;
        if(outque[u] > N+1) //如果出队次数大于N，则说明出现负环
        {
            ans = -1;
            break;
        }
        for(int i = Head[u]; i != -1; i = Edges[i].next){
            int temp = Dist[u] + Edges[i].w;
            if(temp < Dist[Edges[i].to]){
                Dist[Edges[i].to] = temp;
                if( !vis[Edges[i].to]){
                    vis[Edges[i].to] = 1;
                    Q.push(Edges[i].to);
                }
            }
        }
    }

    if(ans == -1)   //出现负权回路，不存在可行解
        printf("-1\n");
    else if(Dist[N] == INF) //可取任意值，都满足差分约束系统
        printf("-2\n");
    else
        printf("%d\n",Dist[N]);  //求使得源点 s 到 终点 t 的最大的值
}

int main(){
    int N,ML,MD,u,v,w;
    while(~scanf("%d%d%d", &N, &ML, &MD)){
        memset(Head,-1,sizeof(Head));
        id = 0;
        for(int i = 0; i < ML; ++i){
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);//建边 u - v <= w
        }
        for(int i = 0; i < MD; ++i){
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(v,u,-w);//建边 v - u <= w
        }
//这里不加也可以
//        for(int i = 1; i < N; ++i)
//            AddEdges(i+1,i,0);
        SPFA(1,N);  //求使得源点 s 到 终点 t 的最大的值
    }
    return 0;
}


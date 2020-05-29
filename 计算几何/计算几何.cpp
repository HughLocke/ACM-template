#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef double db;
const db pi=acos(-1),eps=1e-10;
struct Point
{
    db x,y;
    Point(db x0=0,db y0=0) : x(x0) , y(y0) { }
    friend bool operator<(Point a,Point b)
    {
        return a.x!=b.x?a.x<b.x:a.y<b.y;
    }
    friend Point operator+(const Point &a,const Point &b)
    {
        return Point(a.x+b.x,a.y+b.y);
    }
    friend Point operator-(const Point &a,const Point &b)
    {
        return Point(a.x-b.x,a.y-b.y);
    }
    friend Point operator*(const Point &a,double b)
    {
        return Point(a.x*b,a.y*b);
    }
    friend Point operator/(const Point &a,double b)
    {
        return Point(a.x/b,a.y/b);
    }
}a,b,c,ans;
typedef Point Vector;
db dcmp(db x)//符号判断
{
    if(fabs(x)<eps)return 0;
    else return x<0?-1:1;
}
db Dot(const Point &a,const Point &b)//点积
{
    return a.x*b.x+a.y*b.y;
}
db Cross(const Point &a,const Point &b)//叉积
{
    return a.x*b.y-a.y*b.x;
}
db Length(const Point &a)//求向量的长度
{
    return sqrt(Dot(a,a));
}
db Angle(const Point &a,const Point &b)//求两个向量的夹角（余弦定理）
{
    return acos(Dot(a,b)/Length(a)/Length(b));
}
Point Rotate(const Point &a,double rad)//逆时针旋转rad
{
    return Point(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}
Point Normal(Point &v)//求单位长度的法向量
{
    db L=Length(v);
    return Point(-v.y/L,v.x/L);
}
Point getLineIntersection(const Point &P,const Point &v,const Point &Q,const Point &w)//求两个线段交点
{
    Vector u=P-Q;
    db t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
bool SegmentProperIntersection(const Point &a1,const Point &b1,const Point &a2,const Point &b2)//两线段规范相交、即每条线段的端点分别在另一条一段的两侧
{
    db c1=Cross(b1-a1,a2-a1),c2=Cross(b1-a1,b2-a1);
    db c3=Cross(b2-a2,a1-a2),c4=Cross(b2-a2,b1-a2);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
bool IsPointOnSegment(Point p,Point a1,Point a2)//点在线段上
{
    return dcmp(Cross(p-a1,p-a2))==0 && dcmp(Dot(p-a1,p-a2))<0;
}
double getDistToLine(const Point &P, const Point &A, const Point &B)//点到直线的有向距离（距离加绝对值）
{
    Vector AB = B-A, AP = P-A;
    return Cross(AB, AP) / Length(AB);
}
int ConvexHull(Point *p,int n,Point *ch)//构造逆时针凸包
{
    sort(p+1,p+n+1);//先按照横坐标再按照纵坐标排序
    int m=0;
    for(int i=1;i<=n;i++)
    {
        while(m>1 && Cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
        ch[++m]=p[i];
    }
    int k=m;
    for(int i=n-1;i;i--)
    {
        while(m>k && Cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
        ch[++m]=p[i];
    }
    if(n>1)m--;
    return m;
}
db PolygonArea(Point *p,int n)//求逆时针构成的多边形（可不凸）面积
{
    db ret=0;
    for(int i=2;i<n;i++)//第一个点是p[1],所以这样循环
        ret+=Cross(p[i]-p[1],p[i+1]-p[1]);
    return ret/2;
}
bool isPointInPolygon(Point p,Point *poly,int n)//点在凸多边形内的判定
{
    int wn=0;
    poly[n+1]=poly[1];
    for(int i=1;i<=n;i++)
    {
        if(IsPointOnSegment(p,poly[i],poly[i+1]))return -1;
        int k=dcmp(Cross(poly[i+1]-poly[i],p-poly[i]));
        int d1=dcmp(poly[i].y-p.y);
        int d2=dcmp(poly[i+1].y-p.y);
        if(k>0 && d1<=0 && d2>0)wn++;
        if(k<0 && d2<=0 && d1>0)wn--;
    }
    if(wn!=0)return 1;
    return 0;
}
db dis2(Point a,Point b)
{
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}
db findDiameter(Point *ch,int m)//旋转卡壳求直径（Diatmeter：直径）
{
    if(m==2)    return dis2(ch[1],ch[2]);
    ch[m+1]=ch[1];
    db rec=0;
    int j=3;
    for(int i=1;i<=m;i++)
    {
        while(Cross(ch[i+1]-ch[i],ch[j]-ch[i])<Cross(ch[i+1]-ch[i],ch[j+1]-ch[i]))
        {
            j=j%m+1;
        }
        rec=max(rec,max(dis2(ch[j],ch[i]),dis2(ch[j],ch[i+1])));
    }
    return rec;
}
struct Line
{
    Point P;
    Vector v;
    db ang;
    Line() {}
    Line(Point P,Vector v):P(P),v(v){ang=atan2(v.y,v.x);}
    friend bool operator<(Line a,Line b)
    {
        return  a.ang<b.ang;
    }
};
Point GetIntersection(Line a,Line b)
{
    Vector u=a.P-b.P;
    db t=Cross(b.v,u)/Cross(a.v,b.v);
    return a.P+a.v*t;
}
bool OnLeft(Line L,Point p)
{
    return Cross(L.v,p-L.P)>=0;
}
int HalfplaneIntersection(Line *L,int n,Point *poly)//半平面交
{
    sort(L+1,L+n+1);
    int first,last;
    Point *p=new Point[n+10];
    Line *q=new Line[n+10];
    q[first=last=0]=L[1];
    for(int i=2;i<=n;i++)
    {
        while(first<last && !OnLeft(L[i],p[last-1]))last--;
        while(first<last && !OnLeft(L[i],p[first]))first++;
        q[++last]=L[i];
        if(fabs(Cross(q[last].v,q[last-1].v))<eps)
        {
            last--;
            if(OnLeft(q[last],L[i].P))q[last]=L[i];
        }
        if(first<last)p[last-1]=GetIntersection(q[last-1],q[last]);
    }
    while(first<last && !OnLeft(q[first],p[last-1]))last--;
    if(last-first<=1)return 0;
    p[last]=GetIntersection(q[last],q[first]);
    int m=0;
    for(int i=first;i<=last;i++)poly[++m]=p[i];
    return m;
}


//湘潭大学G题 HDU 6538
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Point
{
    long long x,y;
    Point(long long x=0,long long y=0):x(x),y(y){}
    Point operator - (const Point &b) const {return Point(x-b.x,y-b.y);}
    bool operator < (const Point &b) const {if(x==b.x)return y>b.y;return x<b.x;}
};

const int maxn=2005;

Point p[maxn];

struct Line
{
    int a,b;
    double k;
};


Line l[maxn*maxn+5];
int order[maxn],pos[maxn];
long long S;

bool cmp(Line a,Line b)
{
    return a.k<b.k;
}

long long Cross(Point a,Point b)
{
    return a.x*b.y-b.x*a.y;
}

long long S_2(int a,int b,int c)
{
    return abs(Cross(p[a]-p[b],p[a]-p[c]));
}


int main()
{
    int n,m;
    while(cin>>n)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%lld %lld",&p[i].x,&p[i].y);
            order[i]=i;
            pos[i]=i;
        }
        m=0;
        sort(p,p+n);
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                l[m].a=i;
                l[m].b=j;
                if(p[i].x==p[j].x)  l[m].k=-1e20;
                else    l[m].k=1.0*(p[j].y-p[i].y)/(p[j].x-p[i].x);
                m++;
            }
        }
        sort(l,l+m,cmp);
        long long MAX=-1,MIN=1e15;
        for(int i=0;i<m;i++)
        {
            int a=l[i].a,b=l[i].b;
            swap(pos[a],pos[b]);
            swap(order[pos[a]],order[pos[b]]);
            int t1=pos[a],t2=pos[b];

            if(t1>t2)   swap(t1,t2);
            if(t1!=0&&t2!=n-1)
            {
                MAX=max(MAX,S_2(a,b,order[0])+S_2(a,b,order[n-1]));
                MIN=min(MIN,S_2(a,b,order[t1-1])+S_2(a,b,order[t2+1]));
            }
        }
        printf("%lld %lld\n",MIN,MAX);
    }
    return 0;
}

/* FFT在字符串匹配中的应用
(1).普通的单模式串匹配(KMP模板题)
模式串A,长度为m，文本串B,长度为n
1.定义A(x),B(y)的匹配函数C(x,y)为(A(x) - B(y))²,若C(x,y)=0，则称A的第x个字符和B的第y个字符匹配
2.定义完全匹配函数P(x) = ∑C(i,x - m + i + 1) (0 <= i <= m - 1) 若P(x)=0，则称B以第x位结束的连续m位，与A完全匹配
3.将A反转为S,同时将S，B代入完全匹配函数P(x),得到
P(x) = ∑[S(m - i - 1) - B(x - m + i + 1)]² (0 <= i <= m - 1)
展开化简，得到
P(x) = ∑S(m - i + 1)² + ∑B(x - m + i + 1)² - 2∑S(m - i - 1)B(x - m + i + 1) (0 <= i <= m - 1)
第一项第二项是一个前缀和，预处理一下就可以，发现第三项的两个系数加起来正好是x,所以第三项可以写为
-2∑S(i)B(j)  (i + j = x) ,这就是一个基本卷积的形式了，可以用FFT做
 */
 void FFT_Match(char *s1,char *s2,int m,int n){
    for(int i=0;i<m;i++) A[i].x=s1[i]-'a'+1;
    for(int i=0;i<n;i++) B[i].x=s2[i]-'a'+1;
    reverse(A,A+m);double T=0;
    for(int i=0;i<m;i++) T+=A[i].x*A[i].x;
    f[0]=B[0].x*B[0].x;
    for(int i=1;i<n;i++) f[i]=f[i-1]+B[i].x*B[i].x;
    FFT(A,len,1);FFT(B,len,1);
    for(int i=0;i<len;i++) g[i]=A[i]*B[i];
    FFT(g,len,-1);
    for(int x=m-1;x<n;x++){
        double P=T+f[x]-f[x-m]-2*g[x].r;
        if(fabs(P)<eps) printf("%d ",x-m+2);
    }
}
/*(2)带有通配符的模式串匹配
这就不能用KMP了，但是对于fft来说，方法和上面相似
1.定义A(x),B(y)的匹配函数C(x,y) = (A(x) - B(y))² * A(x) * B(y); 将通配符*的值赋0,表示除了他俩相等，还有出现通配符的情况都算匹配
2.定义完全匹配书P(x) = ∑C(i,x - m + i + 1) (0 <= i <= m - 1)若P(x)=0，则称B以第x位结束的连续m位，与A完全匹配
3.将A反转为S,同时将S,B代入完全匹配函数P(x),得到
P(x) = ∑[S(m - i - 1) - B(x - m + i + 1)]² * S(m - i - ) * B(x - m + i + 1)   (0 <= i <= m - 1)
展开化简,得到
P(x) = ∑S(m - i - 1)³B(x - m + i + 1) + ∑S(m - i - 1)B(x - m + i + 1)³ - 2∑S(m - i - 1)²B(x - m + i + 1)² (0 <= i <= m - 1)
因为(m - i + 1) + (x - m + i + 1) = x,所以
P(x) = ∑S(i)³B(j) + ∑S(i)B(j)³ - 2∑S(i)²B(j)²  (i + j = x)
三段fft可以解决
 */
 const int maxn = 3e5 + 10;
const double PI = acos(-1.0); 
int N,M,K;
char str1[maxn],str2[maxn];
struct complex{
    double x,y;
    complex(double x = 0,double y = 0):x(x),y(y){}
    void init(){x = y = 0;}
    friend complex operator + (complex a,complex b){return complex(a.x + b.x,a.y + b.y);}
    friend complex operator - (complex a,complex b){return complex(a.x - b.x,a.y - b.y);}
    friend complex operator * (complex a,complex b){return complex(a.x * b.x - a.y * b.y,a.x * b.y + a.y * b.x);}
}a[maxn << 2],b[maxn << 2],ans[maxn << 2];
int ca[maxn],cb[maxn];
int r[maxn << 2];
vector<int>s;
void FFT(int limit,complex *A,int *r,int type){
    for(int i = 0 ; i < limit; i ++){
        if(i < r[i]) swap(A[i],A[r[i]]);
    }
    for(int mid = 1; mid < limit; mid <<= 1){
        int len = mid << 1;
        complex Wn(cos(PI/mid),type * sin(PI/mid));
        for(int j = 0 ; j < limit; j += len){
            complex w(1,0);
            for(int k = 0 ; k < mid; k ++,w = w * Wn){
                complex x = A[j + k],y = w * A[j + mid + k];
                A[j + k] = x + y;
                A[j + mid + k] = x - y;
            }
        }
    }
}
inline double cul(double x,int y){
    if(y == 1) return x;
    if(y == 2) return x * x;
    return x * x * x;
}
int main(){
    Sca2(N,M);
    scanf("%s%s",str1,str2); //长串str2,短串str1
    for(int i = 0 ; i < N / 2; i ++) swap(str1[i],str1[N - i - 1]);
    int limit = 1,l = 0;
    while(limit <= N + M - 2) limit <<= 1,l++;
    for(int i = 0 ; i < limit; i ++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    for(int i = 0 ; i < N ; i ++) if(str1[i] != '*') ca[i] = str1[i] - 'a' + 1;
    for(int i = 0 ; i < M ; i ++) if(str2[i] != '*') cb[i] = str2[i] - 'a' + 1;
    for(int k = 1; k <= 3; k ++){
        for(int i = 0 ; i < limit; i ++) a[i].init(),b[i].init();
        for(int i = 0 ; i < N ; i ++) a[i].x = cul(ca[i],k);
        for(int i = 0 ; i < M ; i ++) b[i].x = cul(cb[i],3 - k + 1);
        FFT(limit,a,r,1); FFT(limit,b,r,1);
        int t = 1; if(k == 2) t = -2;
        for(int i = 0 ; i < limit; i ++) ans[i] = ans[i] + t * a[i] * b[i];
    }
    FFT(limit,ans,r,-1);
    for(int i = N - 1; i < M; i ++){   //一般短串逆置的范围 
        if(!(int)(ans[i].x / limit + 0.5)) s.push_back(i - N + 2);
    }
    Pri(s.size());
    for(int i = 0 ; i < s.size(); i ++) printf("%d ",s[i]);
    return 0;
}
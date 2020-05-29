//求出ax + by = c的一组可行解
//有解的前提 gcd(a,b)|c ,否则无解
LL exgcd(LL a,LL b,LL &x,LL &y){
    if(a == 0 && b == 0) return -1;
    if(b == 0){
        x = 1;y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}
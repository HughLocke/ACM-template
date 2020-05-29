//miller_robin素数测试
LL q_p(LL a,LL b,LL mod){
    LL ans = 1;
    while(b){
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
LL Test[10] = {2,3,5,7,11,13,17};
bool Miller_robin(LL p){
    if(p == 1) return 0;
    LL t = p - 1,k = 0;
    while(!(t & 1)) k++,t >>= 1;
    for(int i = 0 ; i < 4; i ++){
        if(p == Test[i]) return true;
        LL a = q_p(Test[i],t,p),nxt = a;
        for(int j = 1; j <= k ; j ++){
            nxt = a * a % p;
            if(nxt == 1 && a != 1 && a != p - 1) return false;
            a = nxt;
        }
        if(a != 1) return false;
    }
    return true;
}